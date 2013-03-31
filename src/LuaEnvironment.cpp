#include "LuaEnvironment.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "LuaStack.hpp"
#include <QTextStream>
#include "LuaException.hpp"
#include "LuaValue.hpp"
#include "ModuleLoader.hpp"
#include "table.hpp"

#include "LuaAccessible.hpp"
#include "LuaGlobalAccessible.hpp"
#include "LuaReferenceAccessible.hpp"

using std::runtime_error;
using std::istream;

namespace {
    struct LuaReadingData
    {
        istream& stream;
        char buffer[4096];
        LuaReadingData(istream& stream) : stream(stream) {}
    };

    struct QtReadingData
    {
        QTextStream stream;
        QByteArray chunk;
        QtReadingData(QFile& file) : stream(&file) {}
    };

    const int CHUNKSIZE = 4096;

    const char* read_stream(lua_State *, void *data, size_t *size)
    {
        LuaReadingData* d = static_cast<LuaReadingData*>(data);
        if (!d->stream)
            return NULL;
        d->stream.read(d->buffer, CHUNKSIZE);
        *size = d->stream.gcount();
        return d->buffer;
    }

    const char* read_qstream(lua_State*, void *pstream, size_t *size)
    {
        QtReadingData* d = static_cast<QtReadingData*>(pstream);
        if(d->stream.atEnd())
            return NULL;
        d->chunk = d->stream.read(CHUNKSIZE).toUtf8();
        *size = d->chunk.size();
        return d->chunk.constData();
    }
}

int throwFromPanic(lua_State* state)
{
    const char* msg = lua_tostring(state, -1);
    throw LuaException(string("Fatal exception from Lua: ") + msg);
}

Lua::Lua()
{
    state = luaL_newstate();
    luaL_openlibs(state);
    lua_atpanic(state, throwFromPanic);

    const char* searchersName = "searchers";
    #if LUA_VERSION_NUM < 502
        searchersName = "loaders";
    #endif

    table::push((*this)["package"][searchersName], Lua::loadModule);
}

LuaValue Lua::operator()(const char* runnable)
{
    luaL_loadstring(state, runnable);
    lua_call(state, 0, 1);
    return LuaValue(
        std::shared_ptr<LuaAccessible>(
            new LuaReferenceAccessible(*this)
        )
    );
}

LuaValue Lua::operator()(const QString& runnable)
{
    return (*this)(runnable.toUtf8().constData());
}

LuaValue Lua::operator()(const string& runnable)
{
    std::istringstream stream(runnable);
    return (*this)(stream, "string input");
}

void Lua::handleLoadValue(const int rv)
{
    switch (rv) {
        case LUA_ERRSYNTAX:
            throw LuaException(this, string("Syntax error during compilation: ") + lua_tostring(state, -1));
        case LUA_ERRMEM:
            throw LuaException(this, string("Memory allocation error during compilation: ") + lua_tostring(state, -1));
    }
}

LuaValue Lua::operator()(istream& stream, const string& name = NULL)
{
    LuaReadingData d(stream);

    handleLoadValue(lua_load(state, &read_stream, &d, name.c_str()
        #if LUA_VERSION_NUM >= 502
            // Account for the extra mode parameter introduced in 5.2
            , NULL
        #endif
    ));
    lua_call(state, 0, 1);
    return LuaValue(
        std::shared_ptr<LuaAccessible>(
            new LuaReferenceAccessible(*this)
        )
    );
}

LuaValue Lua::operator()(QFile& file)
{
    if (!file.open(QIODevice::ReadOnly)) {
        throw LuaException(this,
            QString("Cannot open file ") +
            file.fileName() + ": " +
            file.errorString());
    }
    QtReadingData d(file);
    handleLoadValue(lua_load(state, &read_qstream, &d, file.fileName().toAscii().constData()
        #if LUA_VERSION_NUM >= 502
            // Account for the extra mode parameter introduced in 5.2
            , NULL
        #endif
    ));
    lua_call(state, 0, 1);
    return LuaValue(
        std::shared_ptr<LuaAccessible>(
            new LuaReferenceAccessible(*this)
        )
    );
}

LuaValue Lua::operator[](const char* key)
{
    return (*this)[QString(key)];
}

LuaValue Lua::operator[](const QString& key)
{
    return LuaValue(
        std::shared_ptr<LuaAccessible>(
            new LuaGlobalAccessible(*this, key)
        )
    );
}

LuaValue Lua::operator[](const string& key)
{
    QString str(key.c_str());
    return (*this)[str];
}

void Lua::addModuleLoader(ModuleLoader* const loader)
{
    _moduleLoaders.push_back(loader);
}

void Lua::removeModuleLoader(ModuleLoader* const loader)
{
    _moduleLoaders.erase(
        std::remove(begin(_moduleLoaders), end(_moduleLoaders), loader),
        end(_moduleLoaders)
    );
}

void Lua::loadModule(LuaStack& stack)
{
    auto moduleName = stack.as<QString>();
    stack.clear();

    Lua& lua = stack.lua();

    for (auto loader : lua._moduleLoaders) {
        if (loader->search(moduleName)) {
            stack << std::function<void()>([=, &lua]() {
                loader->load(lua, moduleName);
            });
            return;
        }
    }

    stack << "Unable to find module: " << moduleName;
}


int Lua::internalStackSize() const
{
    return lua_gettop(state);
}

void Lua::collectGarbage()
{
    lua_gc(state, LUA_GCCOLLECT, 0);
}

Lua::~Lua()
{
    lua_close(state);
}

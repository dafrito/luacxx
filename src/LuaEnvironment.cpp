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

#include "LuaGlobalAccessible.hpp"

#include <lauxlib.h>
#include <lualib.h>

namespace {
    struct LuaReadingData
    {
        std::istream& stream;
        char buffer[4096];
        LuaReadingData(std::istream& stream) : stream(stream) {}
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
        if (d->stream.eof()) {
            return NULL;
        }
        d->stream.readsome(d->buffer, CHUNKSIZE);
        if (d->stream.fail()) {
            throw std::runtime_error("Error while reading stream");
        }
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
    throw LuaException(std::string("Panic from Lua: ") + msg);
}

LuaEnvironment::LuaEnvironment() :
    _acceptsStackUserdata(false)
{
    state = luaL_newstate();
    luaL_openlibs(state);
    lua_atpanic(state, throwFromPanic);

    const char* searchersName = "searchers";
    #if LUA_VERSION_NUM < 502
        searchersName = "loaders";
    #endif

    table::push((*this)["package"][searchersName], LuaEnvironment::loadModule);
}

void LuaEnvironment::setAcceptsStackUserdata(const bool accepts)
{
    _acceptsStackUserdata = accepts;
    lua_pushstring(luaState(), "acceptsStackUserdata");
    lua_pushboolean(luaState(), accepts);
    lua_settable(luaState(), LUA_REGISTRYINDEX);
}

LuaReference LuaEnvironment::newReference()
{
    LuaStack stack(luaState());
    lua::push(stack, lua::value::nil);

    return LuaReference(
        luaState(),
        LuaReferenceAccessible(luaState(), stack.saveAndPop())
    );
}

LuaReference innerInvoke(LuaStack& stack)
{
    int funcLoc = stack.top();
    stack.invoke();
    if (stack.top() >= funcLoc) {
        return LuaReference(
            stack.luaState(),
            LuaReferenceAccessible(stack.luaState(), stack.save(funcLoc))
        );
    }
    return LuaReference(
        stack.luaState(),
        LuaReferenceAccessible(stack.luaState())
    );
}

LuaReference LuaEnvironment::operator()(const char* runnable)
{
    LuaStack stack(luaState());
    luaL_loadstring(state, runnable);
    return innerInvoke(stack);
}

LuaReference LuaEnvironment::operator()(const std::string& runnable)
{
    std::istringstream stream(runnable);
    return (*this)(stream, "string input");
}

void LuaEnvironment::handleLoadValue(const int rv)
{
    switch (rv) {
        case LUA_ERRSYNTAX:
            throw LuaException(std::string("Syntax error during compilation: ") + lua_tostring(state, -1));
        case LUA_ERRMEM:
            throw std::runtime_error(std::string("Memory allocation error during compilation: ") + lua_tostring(state, -1));
    }
}

LuaReference LuaEnvironment::operator()(std::istream& stream, const std::string& name)
{
    LuaReadingData d(stream);

    if (!stream) {
        throw std::runtime_error(std::string("Input stream is invalid for '") + name + "'");
    }

    LuaStack stack(luaState());
    handleLoadValue(lua_load(state, &read_stream, &d, name.c_str()
        #if LUA_VERSION_NUM >= 502
            // Account for the extra mode parameter introduced in 5.2
            , NULL
        #endif
    ));
    return innerInvoke(stack);
}

LuaReference LuaEnvironment::operator()(QFile& file)
{
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error(
            (QString("Cannot open file ") + file.fileName() + ": " + file.errorString()).toStdString()
        );
    }
    QtReadingData d(file);
    LuaStack stack(luaState());
    handleLoadValue(lua_load(state, &read_qstream, &d, file.fileName().toUtf8().constData()
        #if LUA_VERSION_NUM >= 502
            // Account for the extra mode parameter introduced in 5.2
            , NULL
        #endif
    ));
    return innerInvoke(stack);
}

LuaGlobal LuaEnvironment::operator[](const char* key)
{
    return (*this)[std::string(key)];
}

LuaGlobal LuaEnvironment::operator[](const std::string& key)
{
    return LuaGlobal(luaState(), LuaGlobalAccessible(key));
}

void LuaEnvironment::addModuleLoader(ModuleLoader* const loader)
{
    _moduleLoaders.push_back(loader);
}

void LuaEnvironment::removeModuleLoader(ModuleLoader* const loader)
{
    _moduleLoaders.erase(
        std::remove(begin(_moduleLoaders), end(_moduleLoaders), loader),
        end(_moduleLoaders)
    );
}

void LuaEnvironment::loadModule(LuaStack& stack)
{
    auto moduleName = stack.get<std::string>();
    stack.clear();

    // TODO Fix this module loading

    /*Lua& lua = stack.lua();

    for (auto loader : lua._moduleLoaders) {
        if (loader->search(moduleName)) {
            lua::push(stack, std::function<void()>([=, &lua]() {
                loader->load(lua, moduleName);
            }));
            return;
        }
    }*/

    lua::push(stack, std::string("Unable to find module: ") + moduleName);
}

int LuaEnvironment::internalStackSize() const
{
    return lua_gettop(state);
}

void LuaEnvironment::collectGarbage()
{
    lua_gc(state, LUA_GCCOLLECT, 0);
}

LuaEnvironment::~LuaEnvironment()
{
    lua_close(state);
}

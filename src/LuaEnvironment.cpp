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

    table::push((*this)["package"][searchersName], std::function<void(LuaStack&)>([this](LuaStack& stack) {
        LuaEnvironment::loadModule(*this, stack);
    }));
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

void LuaEnvironment::loadModule(LuaEnvironment& lua, LuaStack& stack)
{
    auto moduleName = stack.get<std::string>();
    stack.clear();

    for (auto loader : lua._moduleLoaders) {
        if (loader->search(moduleName)) {
            lua::push(stack, std::function<void()>([=, &lua]() {
                loader->load(lua, moduleName);
            }));
            return;
        }
    }

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

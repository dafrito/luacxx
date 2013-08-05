#ifndef HEADER_LUA_ENVIRONMENT_HPP
#define HEADER_LUA_ENVIRONMENT_HPP

#include <string>
#include <istream>
#include <lua.hpp>
#include <vector>

#include "LuaStack.hpp"
#include "values.hpp"
#include "qobject.hpp"
#include "loaders.hpp"

class ModuleLoader;

class LuaEnvironment
{
    lua_State* state;

    bool _acceptsStackUserdata;

    std::vector<ModuleLoader*> _moduleLoaders;

    static void loadModule(LuaEnvironment& lua, LuaStack& stack);
public:
    LuaEnvironment();
    ~LuaEnvironment();

    LuaReference newReference();

    template<class Input>
    LuaReference operator()(Input input)
    {
        return lua::runString(*this, input);
    }

    LuaGlobal operator[](const char* key);
    LuaGlobal operator[](const std::string& key);

    bool acceptsStackUserdata() const
    {
        return _acceptsStackUserdata;
    }

    void setAcceptsStackUserdata(const bool accepts);

    void addModuleLoader(ModuleLoader* const loader);
    void removeModuleLoader(ModuleLoader* const loader);

    void collectGarbage();

    lua_State* luaState() const
    {
        return state;
    }

    int internalStackSize() const;
};

#endif // HEADER_LUA_ENVIRONMENT_HPP

#ifndef HEADER_LUA_ENVIRONMENT_HPP
#define HEADER_LUA_ENVIRONMENT_HPP

#include <string>
#include <istream>
#include <lua.hpp>
#include <QFile>
#include <vector>

#include "LuaStack.hpp"
#include "LuaGlobalAccessible.hpp"

class ModuleLoader;

class Lua
{
    lua_State* state;

    bool _acceptsStackUserdata;

    std::vector<ModuleLoader*> _moduleLoaders;

    void handleLoadValue(const int rv);

    static void loadModule(LuaStack& stack);
public:
    Lua();
    ~Lua();

    LuaGlobal operator[](const char* key);
    LuaGlobal operator[](const std::string& key);

    LuaReference operator()(const char* runnable);
    LuaReference operator()(const std::string& runnable);
    LuaReference operator()(std::istream& stream, const std::string& name);
    LuaReference operator()(QFile& file);

    bool acceptsStackUserdata() const
    {
        return _acceptsStackUserdata;
    }

    void setAcceptsStackUserdata(const bool accepts)
    {
        _acceptsStackUserdata = accepts;
    }

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

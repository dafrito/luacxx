#ifndef HEADER_LUA_ENVIRONMENT_HPP
#define HEADER_LUA_ENVIRONMENT_HPP

#include <string>
#include <istream>
#include <lua.hpp>
#include <QFile>
#include <vector>

#include "LuaStack.hpp"
#include "values.hpp"
#include "qobject.hpp"

class ModuleLoader;

class LuaEnvironment
{
    lua_State* state;

    bool _acceptsStackUserdata;

    std::vector<ModuleLoader*> _moduleLoaders;

    void handleLoadValue(const int rv);

    static void loadModule(LuaEnvironment& lua, LuaStack& stack);
public:
    LuaEnvironment();
    ~LuaEnvironment();

    LuaReference newReference();

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

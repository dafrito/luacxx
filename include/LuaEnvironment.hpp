#ifndef HEADER_LUA_ENVIRONMENT_HPP
#define HEADER_LUA_ENVIRONMENT_HPP

#include <QObject>
#include <string>
#include <istream>
#include <lua.hpp>
#include <QFile>
#include <vector>

using std::istream;
using std::string;

class LuaValue;
class ModuleLoader;
class LuaStack;

class Lua : public QObject
{
    Q_OBJECT

    lua_State* state;

    std::vector<ModuleLoader*> _moduleLoaders;

    void handleLoadValue(const int rv);

    static void loadModule(Lua& lua, LuaStack& stack);
public:
    Lua();
    ~Lua();

    LuaValue operator[](const char* key);
    LuaValue operator[](const QString& key);
    LuaValue operator[](const string& key);

    LuaValue operator()(const char* runnable);
    LuaValue operator()(const string& runnable);
    LuaValue operator()(const QString& runnable);
    LuaValue operator()(istream& stream, const string& name);
    LuaValue operator()(QFile& file);

    void addModuleLoader(ModuleLoader* const loader);
    void removeModuleLoader(ModuleLoader* const loader);

    int internalStackSize() const;

    friend class LuaStack;
    friend class LuaValue;
    friend class LuaAccessible;
};

#endif // HEADER_LUA_ENVIRONMENT_HPP

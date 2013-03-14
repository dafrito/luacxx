#ifndef HEADER_LUA_ENVIRONMENT_HPP
#define HEADER_LUA_ENVIRONMENT_HPP

#include <QObject>
#include <string>
#include <istream>
#include <lua.hpp>
#include <QFile>

using std::istream;
using std::string;

class LuaValue;

class Lua : public QObject
{
    Q_OBJECT

    lua_State* state;

    void handleLoadValue(const int rv);
public:
    Lua();
    ~Lua();

    LuaValue operator[](const char* key);
    LuaValue operator[](const QString& key);
    LuaValue operator[](const string& key);

    void operator()(const char* runnable);
    void operator()(const string& runnable);
    void operator()(const QString& runnable);
    void operator()(istream& stream, const string& name);
    void operator()(QFile& file);

    friend class LuaStack;
    friend class LuaValue;
    friend class LuaAccessible;
};

#endif // HEADER_LUA_ENVIRONMENT_HPP

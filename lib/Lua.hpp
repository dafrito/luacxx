#ifndef HEADER_LUA_HPP
#define HEADER_LUA_HPP

#include <QObject>
#include <string>
#include <istream>
#include <lua.hpp>
#include <QFile>

class LuaGlobal;

using std::istream;
using std::string;

class Lua : public QObject
{
	Q_OBJECT

	lua_State * state;
public:
	Lua();
	~Lua();

	LuaGlobal operator[](const char* key);
	LuaGlobal operator[](const QString& key);
	LuaGlobal operator[](const string& key);

	void operator()(const string& runnable);
	void operator()(istream& stream, const string& name);
	void operator()(QFile& file);

	friend class LuaStack;
	friend class LuaValue;
};

#endif

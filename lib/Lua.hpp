#ifndef HEADER_LUA_HPP
#define HEADER_LUA_HPP

#include <QObject>
#include <string>
#include <istream>

#include "LuaValue.hpp"

using std::istream;
using std::string;

class Lua : public QObject
{
	Q_OBJECT

	lua_State * state;
public:
	Lua();
	~Lua();

	LuaValue operator[](const string& key);

	void operator()(istream& stream, const string& name);

	friend class LuaStack;
};

#endif

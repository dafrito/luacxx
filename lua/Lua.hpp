#ifndef HEADER_LUA_HPP
#define HEADER_LUA_HPP

#include <string>
#include <istream>
#include <lua.hpp>

#include "LuaValue.hpp"

using std::istream;
using std::string;

class Lua
{
	lua_State * state;
public:
	Lua();
	~Lua();

	LuaValue operator[](const string& key);

	void operator()(istream& stream, const string& name);

	friend class LuaValue;
};

#endif

#ifndef HEADER_LUA_HPP
#define HEADER_LUA_HPP

#include <string>
#include <lua.hpp>

using std::string;

class Lua
{
private:
	lua_State * state;
public:

	class LuaValue
	{
	private:
		Lua& lua;
		string key;
	public:
		LuaValue(Lua& lua, const string& key) :
			lua(lua), key(key) {}

		const LuaValue& operator=(const char *value);
	};
	Lua();
	~Lua();

	LuaValue operator[](const string& key);

	friend class LuaValue;
};

#endif

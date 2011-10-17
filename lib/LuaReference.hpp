#ifndef LUAREFERENCE_HPP
#define LUAREFERENCE_HPP

#include "LuaValue.hpp"

class LuaReference : public LuaValue
{
	int ref;
protected:
	void push(LuaStack&) const
	{
		lua_rawgeti(lua.state, LUA_REGISTRYINDEX, ref);
	}
public:
	LuaReference(Lua& lua) : LuaValue(lua)
	{
		ref = luaL_ref(lua.state, LUA_REGISTRYINDEX);
	}

	~LuaReference()
	{
		luaL_unref(lua.state, LUA_REGISTRYINDEX, ref);
	}

	template<typename T>
	const LuaReference& operator=(const T& value)
	{
		LuaStack s(lua);
		s.push(value);
		lua_rawseti(lua.state, LUA_REGISTRYINDEX, ref);
		return *this;
	}
};

#endif // LUAREFERENCE_HPP

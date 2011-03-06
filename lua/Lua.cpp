#include "Lua.hpp"

Lua::Lua()
{
	state = luaL_newstate();
}

Lua::~Lua()
{
	lua_close(state);
}

const Lua::LuaValue& Lua::LuaValue::operator=(const char *value)
{
	return *this;
}

Lua::LuaValue Lua::operator[](const string& key)
{
	return Lua::LuaValue(*this, key);
}

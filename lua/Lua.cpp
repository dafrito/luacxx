#include "Lua.hpp"
#include <cstring>

Lua::Lua()
{
	state = luaL_newstate();
}

Lua::~Lua()
{
	lua_close(state);
}

const char* Lua::LuaValue::char_value() const
{
	lua_getglobal(lua.state, key.c_str());
	return lua_tostring(lua.state, -1);
}

const Lua::LuaValue& Lua::LuaValue::operator=(const char *value)
{
	lua_pushstring(lua.state, value);
	lua_setglobal(lua.state, key.c_str());
	return *this;
}

Lua::LuaValue Lua::operator[](const string& key)
{
	return Lua::LuaValue(*this, key);
}

Lua::LuaValue::operator string()
{
	return string(char_value());
}

Lua::LuaValue::operator const char*()
{
	return char_value();
}

bool Lua::LuaValue::operator==(const char* other)
{
	return !strcmp(char_value(), other);
}

bool Lua::LuaValue::operator==(const string& other)
{
	return other == char_value();
}

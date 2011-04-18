#include <cstring>

#include "LuaValue.hpp"
#include "Lua.hpp"
#include "LuaStack.hpp"

const char* LuaValue::char_value() const
{
	return LuaStack(lua).global(key).cstring();
}

LuaValue::operator const char*() const
{
	return char_value();
}

LuaValue::operator string() const
{
	return LuaStack(lua).global(key).string();
}

LuaValue::operator bool() const
{
	return LuaStack(lua).global(key).boolean();
}

LuaValue::operator int() const
{
	return LuaStack(lua).global(key).number();
}

LuaValue::operator lua_Number() const
{
	return LuaStack(lua).global(key).number();
}

bool LuaValue::operator==(const char* other) const
{
	return !strcmp(char_value(), other);
}

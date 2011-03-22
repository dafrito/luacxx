#include <cstring>

#include "LuaValue.hpp"
#include "Lua.hpp"
#include "LuaStack.hpp"

const LuaValue& LuaValue::operator=(const char *value)
{
	LuaStack(lua).setGlobal(key, value);
	return *this;
}

const char* LuaValue::char_value() const
{
	return LuaStack(lua).global(key).cstring();
}

LuaValue::operator const char*()
{
	return LuaStack(lua).global(key).cstring();
}

LuaValue::operator string()
{
	return LuaStack(lua).global(key).string();
}

bool LuaValue::operator==(const char* other)
{
	return !strcmp(char_value(), other);
}

bool LuaValue::operator==(const string& other)
{
	return other == char_value();
}


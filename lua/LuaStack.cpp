#include "Lua.hpp"
#include "LuaStack.hpp"
#include "exceptions.hpp"

LuaStack::LuaStack(Lua& lua) :
	lua(lua),
	initialPosition(lua_gettop(lua.state)),
	minimumSize(0)
{}

LuaStack::LuaStack(Lua& lua, int initialPosition, int minimumSize) :
	lua(lua),
	initialPosition(initialPosition),
	minimumSize(minimumSize)
{}


bool LuaStack::isMagicalPos(const int& pos)
{
	return pos == LUA_GLOBALSINDEX;
}

void LuaStack::checkPos(const int& pos)
{
	if (isMagicalPos(pos))
		return;
	const int top=lua_gettop(lua.state);
	if (top + pos < initialPosition)
		throw LuaException(lua, "Stack position is not managed by this stack");
	if (pos >= 0)
		throw LuaException(lua, "Stack position is non-negative");
}

void LuaStack::checkSize(const int& min)
{
	if(min > lua_gettop(lua.state) - initialPosition)
		throw LuaException(lua, "Stack size is too small");
}

const char* LuaStack::cstring(int pos)
{
	checkPos(pos);
	return lua_tostring(lua.state, pos);
}

std::string LuaStack::string(int pos)
{
	checkPos(pos);
	return std::string(cstring(pos));
}

double LuaStack::number(int pos)
{
	checkPos(pos);
	return lua_tonumber(lua.state, pos);
}

LuaStack& LuaStack::global(const char* name)
{
	lua_getglobal(lua.state, name);
	return (*this);
}

LuaStack& LuaStack::global(const std::string& name)
{
	global(name.c_str());
	return (*this);
}

LuaStack& LuaStack::set(const char* key, int tablePos)
{
	checkPos(tablePos);
	lua_setfield(lua.state, tablePos, key);
	return (*this);
}

LuaStack& LuaStack::set(const std::string& key, int tablePos)
{
	return set(key.c_str(), tablePos);
}

LuaStack& LuaStack::push(const char* value)
{
	lua_pushstring(lua.state, value);
	return (*this);
}

LuaStack& LuaStack::push(const std::string& value)
{
	return push(value.c_str());
}

LuaStack& LuaStack::push(const lua_Number& value)
{
	lua_pushnumber(lua.state, value);
	return (*this);
}

LuaStack& LuaStack::push(const bool& value)
{
	lua_pushboolean(lua.state, value);
	return (*this);
}

LuaStack& LuaStack::push(lua_CFunction f)
{
	lua_pushcfunction(lua.state, f);
	return (*this);
}

LuaStack::~LuaStack()
{
	int popped=lua_gettop(lua.state) - initialPosition;
	if (popped > 0)
		lua_pop(lua.state, max(0, popped - minimumSize));
	else if (popped < 0)
		throw LuaException(lua, "Stack underflow");
}

#include "Lua.hpp"
#include "LuaStack.hpp"
#include "exceptions.hpp"

LuaStack::LuaStack(Lua& lua) : lua(lua)
{
	initialPosition=lua_gettop(lua.state);
}

const char* LuaStack::cstring(int pos)
{
	return lua_tostring(lua.state, pos);
}

std::string LuaStack::string(int pos)
{
	return std::string(cstring(pos));
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

LuaStack::~LuaStack()
{
	int popped=lua_gettop(lua.state) - initialPosition;
	if (popped > 0)
		lua_pop(lua.state, popped);
	else if (popped < 0)
		throw LuaException(lua, "Stack underflow");
}

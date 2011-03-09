#ifndef HEADER_LUASTACK_HPP
#define HEADER_LUASTACK_HPP

#include <string>

class Lua;

class LuaStack
{
private:
	Lua& lua;
	int initialPosition;
public:
	LuaStack(Lua& lua);
	const char* cstring(int pos = -1);
	std::string string(int pos = -1);
	LuaStack& global(const char* name);
	LuaStack& global(const std::string& name);
	~LuaStack();
};

#endif

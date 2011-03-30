#ifndef HEADER_LUAFUNCTION_HPP
#define HEADER_LUAFUNCTION_HPP

#include <functional>

class Lua;
class LuaStack;

typedef std::function<void (Lua& lua, LuaStack& stack)> LuaCallable;

class ForwardingLuaFunction
{
	Lua& lua;
	LuaCallable f;

	void operator()();
public:
	ForwardingLuaFunction(Lua& lua, LuaCallable f) : lua(lua), f(f) {}

	friend class LuaStack;
};

#endif

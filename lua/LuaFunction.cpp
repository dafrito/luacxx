#include "LuaFunction.hpp"
#include "LuaStack.hpp"
#include "Lua.hpp"

void ForwardingLuaFunction::operator ()()
{
	LuaStack stack(lua);
	stack.offset(0);
	f(lua, stack);
	stack.offset(stack.size());
}

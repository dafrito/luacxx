#include "metatables.hpp"

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable)
{
    stack.push(LuaUserdata(callable, "lua::LuaCallable"));
}

LuaStack& operator>>(LuaStack& stack, std::shared_ptr<lua::LuaCallable>& callable)
{
    return lua::metatable::convertFromUserdata(stack, callable, "lua::LuaCallable");
}

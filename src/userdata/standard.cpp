#include "userdata.hpp"

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable)
{
    stack.push(LuaUserdata(callable, "lua::LuaCallable"));
}

LuaStack& operator>>(LuaStack& stack, std::shared_ptr<lua::LuaCallable>& callable)
{
    return lua::userdata::convertUserdata(stack, callable, "lua::LuaCallable");
}

#include "userdata.hpp"

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable)
{
    return stack << LuaUserdata(callable, "lua::LuaCallable");
}

LuaIndex& operator>>(LuaIndex& index, std::shared_ptr<lua::LuaCallable>& callable)
{
    return lua::userdata::convertUserdata(index, callable, "lua::LuaCallable");
}

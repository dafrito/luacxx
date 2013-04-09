#include "userdata.hpp"

LuaStack& operator<<(LuaStack& stack, const std::shared_ptr<lua::LuaCallable>& callable)
{
    return stack << LuaUserdata(callable, "lua::LuaCallable");
}

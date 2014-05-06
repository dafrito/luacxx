#include "thread.hpp"

int lua::size(const lua::thread& env)
{
    return lua_gettop(env.state());
}


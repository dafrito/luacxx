#include "luacxx/thread.hpp"

int lua::size(const lua::thread& env)
{
    return lua_gettop(env.state());
}

lua::thread lua::create()
{
    lua::thread env(luaL_newstate());
    env.set_as_owner();
    luaL_openlibs(env);
    return env;
}


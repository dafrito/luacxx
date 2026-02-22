#include "QString.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

void lua::QString_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
}

int QString_new(lua_State* const state)
{
    lua::make<QString>(state);
    return 1;
}

int luaopen_Qt5Core_QString(lua_State* const state)
{
    lua::thread env(state);

    env["QString"] = lua::value::table;
    env["QString"]["new"] = QString_new;
    auto t = env["QString"];

    return 0;
}

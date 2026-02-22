#include "QFlags.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

int luaopen_Qt5Core_QFlags(lua_State* const state)
{
    lua::thread env(state);

    env["QFlags"] = lua::value::table;

    return 0;
}

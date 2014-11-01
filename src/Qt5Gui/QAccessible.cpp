#include "QAccessible.hpp"
#include "../convert/const_char_p.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

int luaopen_Qt5Gui_QAccessible(lua_State* const state)
{
    lua::thread env(state);

    env["QAccessible"] = lua::value::table;
    auto t = env["QAccessible"];

    return 0;
}

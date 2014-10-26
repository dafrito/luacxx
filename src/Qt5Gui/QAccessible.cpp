#include "QAccessible.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QAccessible_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QAccessible_new(lua_State* const state)
{
    lua::make<QAccessible>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Gui_QAccessible(lua_State* const state)
{
    lua::thread env(state);

    env["QAccessible"] = lua::value::table;
    env["QAccessible"]["new"] = QAccessible_new;
    auto t = env["QAccessible"];

    return 0;
}

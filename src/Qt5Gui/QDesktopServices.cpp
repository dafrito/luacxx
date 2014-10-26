#include "QDesktopServices.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QDesktopServices_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QDesktopServices_new(lua_State* const state)
{
    lua::make<QDesktopServices>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Gui_QDesktopServices(lua_State* const state)
{
    lua::thread env(state);

    env["QDesktopServices"] = lua::value::table;
    env["QDesktopServices"]["new"] = QDesktopServices_new;
    auto t = env["QDesktopServices"];

    return 0;
}

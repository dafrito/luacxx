#include "QTextBlockUserData.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QTextBlockUserData_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
}

} // namespace lua

int luaopen_Qt5Gui_QTextBlockUserData(lua_State* const state)
{
    lua::thread env(state);

    env["QTextBlockUserData"] = lua::value::table;

    return 0;
}

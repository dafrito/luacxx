#include "QFontDatabase.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QFontDatabase_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QFontDatabase_new(lua_State* const state)
{
    lua::make<QFontDatabase>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Gui_QFontDatabase(lua_State* const state)
{
    lua::thread env(state);

    env["QFontDatabase"] = lua::value::table;
    env["QFontDatabase"]["new"] = QFontDatabase_new;
    auto t = env["QFontDatabase"];

    return 0;
}

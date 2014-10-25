#include "QTextEdit.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QTextEdit_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QTextEdit_new(lua_State* const state)
{
    lua::make<QTextEdit>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Widgets_QTextEdit(lua_State* const state)
{
    lua::thread env(state);

    env["QTextEdit"] = lua::value::table;
    env["QTextEdit"]["new"] = QTextEdit_new;
    auto t = env["QTextEdit"];

    return 0;
}

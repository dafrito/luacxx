#include "QSyntaxHighlighter.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QSyntaxHighlighter_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QSyntaxHighlighter_new(lua_State* const state)
{
    lua::make<QSyntaxHighlighter>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Gui_QSyntaxHighlighter(lua_State* const state)
{
    lua::thread env(state);

    env["QSyntaxHighlighter"] = lua::value::table;
    env["QSyntaxHighlighter"]["new"] = QSyntaxHighlighter_new;
    auto t = env["QSyntaxHighlighter"];

    return 0;
}

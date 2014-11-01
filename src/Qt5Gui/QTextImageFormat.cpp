#include "QTextImageFormat.hpp"

#include "../convert/const_char_p.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QTextImageFormat_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QTextImageFormat_new(lua_State* const state)
{
    lua::make<QTextImageFormat>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Gui_QTextImageFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QTextImageFormat"] = lua::value::table;
    env["QTextImageFormat"]["new"] = QTextImageFormat_new;
    auto t = env["QTextImageFormat"];

    return 0;
}

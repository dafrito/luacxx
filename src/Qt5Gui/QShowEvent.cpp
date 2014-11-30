#include "QShowEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

// http://qt-project.org/doc/qt-5/qshowevent.html

namespace lua {

void QShowEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);
}

} // namespace lua

int QShowEvent_new(lua_State* const state)
{
    lua::make<QShowEvent>(state);

    return 1;
}

int luaopen_Qt5Gui_QShowEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QShowEvent"] = lua::value::table;
    env["QShowEvent"]["new"] = QShowEvent_new;
    auto t = env["QShowEvent"];

    return 0;
}

#include "QHideEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

// http://qt-project.org/doc/qt-5/qhideevent.html

namespace lua {

void QHideEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);
}

} // namespace lua

int QHideEvent_new(lua_State* const state)
{
    lua::make<QHideEvent>(state);

    return 1;
}

int luaopen_Qt5Gui_QHideEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QHideEvent"] = lua::value::table;
    env["QHideEvent"]["new"] = QHideEvent_new;
    auto t = env["QHideEvent"];

    return 0;
}

#include "QWindowStateChangeEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

// http://qt-project.org/doc/qt-5/qwindowstatechangeevent.html

namespace lua {

void QWindowStateChangeEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["oldState"] = &QWindowStateChangeEvent::oldState;
}

} // namespace lua

int luaopen_Qt5Gui_QWindowStateChangeEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QWindowStateChangeEvent"] = lua::value::table;
    auto t = env["QWindowStateChangeEvent"];

    return 0;
}

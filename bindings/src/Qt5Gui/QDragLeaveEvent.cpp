#include "QDragLeaveEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

// http://qt-project.org/doc/qt-5/qdragleaveevent.html

namespace lua {

void QDragLeaveEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);
}

} // namespace lua

int QDragLeaveEvent_new(lua_State* const state)
{
    lua::make<QDragLeaveEvent>(state);

    return 1;
}

int luaopen_Qt5Gui_QDragLeaveEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QDragLeaveEvent"] = lua::value::table;
    env["QDragLeaveEvent"]["new"] = QDragLeaveEvent_new;
    auto t = env["QDragLeaveEvent"];

    return 0;
}

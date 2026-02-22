#include "QCloseEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

// http://qt-project.org/doc/qt-5/qcloseevent.html

namespace lua {

void QCloseEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);
}

} // namespace lua

int QCloseEvent_new(lua_State* const state)
{
    lua::make<QCloseEvent>(state);
    return 1;
}

int luaopen_Qt5Gui_QCloseEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QCloseEvent"] = lua::value::table;
    env["QCloseEvent"]["new"] = QCloseEvent_new;
    auto t = env["QCloseEvent"];

    return 0;
}

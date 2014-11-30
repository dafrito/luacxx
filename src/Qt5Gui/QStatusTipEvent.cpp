#include "QStatusTipEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"

// http://qt-project.org/doc/qt-5/qstatustipevent.html

namespace lua {

void QStatusTipEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["tip"] = &QStatusTipEvent::tip;
}

} // namespace lua

int QStatusTipEvent_new(lua_State* const state)
{
    lua::make<QStatusTipEvent>(state, lua::get<QString>(state, 1));

    return 1;
}

int luaopen_Qt5Gui_QStatusTipEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QStatusTipEvent"] = lua::value::table;
    env["QStatusTipEvent"]["new"] = QStatusTipEvent_new;
    auto t = env["QStatusTipEvent"];

    return 0;
}

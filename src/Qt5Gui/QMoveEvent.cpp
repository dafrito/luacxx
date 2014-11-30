#include "QMoveEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPoint.hpp"

// http://qt-project.org/doc/qt-5/qmoveevent.html

namespace lua {

void QMoveEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["oldPos"] = &QMoveEvent::oldPos;
    mt["pos"] = &QMoveEvent::pos;
}

} // namespace lua

int QMoveEvent_new(lua_State* const state)
{
    // QMoveEvent(const QPoint & pos, const QPoint & oldPos)
    lua::make<QMoveEvent>(state,
        lua::get<const QPoint&>(state, 1),
        lua::get<const QPoint&>(state, 2)
    );

    return 1;
}

int luaopen_Qt5Gui_QMoveEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QMoveEvent"] = lua::value::table;
    env["QMoveEvent"]["new"] = QMoveEvent_new;
    auto t = env["QMoveEvent"];

    return 0;
}

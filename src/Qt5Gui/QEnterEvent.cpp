#include "QEnterEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QPointF.hpp"

// http://qt-project.org/doc/qt-5/qenterevent.html

namespace lua {

void QEnterEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["globalPos"] = &QEnterEvent::globalPos;
    mt["globalX"] = &QEnterEvent::globalX;
    mt["globalY"] = &QEnterEvent::globalY;
    mt["localPos"] = &QEnterEvent::localPos;
    mt["pos"] = &QEnterEvent::pos;
    mt["screenPos"] = &QEnterEvent::screenPos;
    mt["windowPos"] = &QEnterEvent::windowPos;
    mt["x"] = &QEnterEvent::x;
    mt["y"] = &QEnterEvent::y;
}

} // namespace lua

int QEnterEvent_new(lua_State* const state)
{
    // QEnterEvent(const QPointF & localPos, const QPointF & windowPos, const QPointF & screenPos)
    lua::make<QEnterEvent>(state,
        lua::get<const QPointF&>(state, 1),
        lua::get<const QPointF&>(state, 2),
        lua::get<const QPointF&>(state, 3)
    );

    return 1;
}

int luaopen_Qt5Gui_QEnterEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QEnterEvent"] = lua::value::table;
    env["QEnterEvent"]["new"] = QEnterEvent_new;
    auto t = env["QEnterEvent"];

    return 0;
}

#include "QMouseEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QPoint.hpp"

// http://qt-project.org/doc/qt-5/qmouseevent.html

namespace lua {

void QMouseEvent_metatable(lua_State* const state, const int pos)
{
    lua::QInputEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["button"] = &QMouseEvent::button;
    mt["buttons"] = &QMouseEvent::buttons;
    mt["flags"] = &QMouseEvent::flags;
    mt["globalPos"] = &QMouseEvent::globalPos;
    mt["globalX"] = &QMouseEvent::globalX;
    mt["globalY"] = &QMouseEvent::globalY;
    mt["localPos"] = &QMouseEvent::localPos;
    mt["pos"] = &QMouseEvent::pos;
    mt["screenPos"] = &QMouseEvent::screenPos;
    mt["source"] = &QMouseEvent::source;
    mt["windowPos"] = &QMouseEvent::windowPos;
    mt["x"] = &QMouseEvent::x;
    mt["y"] = &QMouseEvent::y;
}

} // namespace lua

int QMouseEvent_new(lua_State* const state)
{
    if (lua::is_type<Qt::MouseButton>(state, 3)) {
        // QMouseEvent(Type type, const QPointF & localPos, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers)
        lua::make<QMouseEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<const QPointF&>(state, 2),
            lua::get<Qt::MouseButton>(state, 3),
            lua::get<Qt::MouseButtons>(state, 4),
            lua::get<Qt::KeyboardModifiers>(state, 5)
        );
    } else if (lua::is_type<Qt::MouseButton>(state, 4)) {
        // QMouseEvent(Type type, const QPointF & localPos, const QPointF & screenPos, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers)
        lua::make<QMouseEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<const QPointF&>(state, 2),
            lua::get<const QPointF&>(state, 3),
            lua::get<Qt::MouseButton>(state, 4),
            lua::get<Qt::MouseButtons>(state, 5),
            lua::get<Qt::KeyboardModifiers>(state, 6)
        );
    } else {
        // QMouseEvent(Type type, const QPointF & localPos, const QPointF & windowPos, const QPointF & screenPos, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers)
        lua::make<QMouseEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<const QPointF&>(state, 2),
            lua::get<const QPointF&>(state, 3),
            lua::get<const QPointF&>(state, 4),
            lua::get<Qt::MouseButton>(state, 5),
            lua::get<Qt::MouseButtons>(state, 6),
            lua::get<Qt::KeyboardModifiers>(state, 7)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QMouseEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QMouseEvent"] = lua::value::table;
    env["QMouseEvent"]["new"] = QMouseEvent_new;
    auto t = env["QMouseEvent"];

    return 0;
}

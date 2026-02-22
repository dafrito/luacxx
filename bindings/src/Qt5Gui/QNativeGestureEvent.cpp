#include "QNativeGestureEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/Qt.hpp"

// http://qt-project.org/doc/qt-5/qnativegestureevent.html

namespace lua {

void QNativeGestureEvent_metatable(lua_State* const state, const int pos)
{
    lua::QInputEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["gestureType"] = &QNativeGestureEvent::gestureType;
    mt["globalPos"] = &QNativeGestureEvent::globalPos;
    mt["localPos"] = &QNativeGestureEvent::localPos;
    mt["pos"] = &QNativeGestureEvent::pos;
    mt["screenPos"] = &QNativeGestureEvent::screenPos;
    mt["value"] = &QNativeGestureEvent::value;
    mt["windowPos"] = &QNativeGestureEvent::windowPos;
}

} // namespace lua

int QNativeGestureEvent_new(lua_State* const state)
{
    // QNativeGestureEvent(Qt::NativeGestureType type, const QPointF & localPos, const QPointF & windowPos, const QPointF & screenPos, qreal realValue, ulong sequenceId, quint64 intValue)
    lua::make<QNativeGestureEvent>(state,
        lua::get<Qt::NativeGestureType>(state, 1),
        lua::get<const QPointF&>(state, 2),
        lua::get<const QPointF&>(state, 3),
        lua::get<const QPointF&>(state, 4),
        lua::get<qreal>(state, 5),
        lua::get<ulong>(state, 6),
        lua::get<quint64>(state, 7)
    );

    return 1;
}

int luaopen_Qt5Gui_QNativeGestureEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QNativeGestureEvent"] = lua::value::table;
    env["QNativeGestureEvent"]["new"] = QNativeGestureEvent_new;
    auto t = env["QNativeGestureEvent"];

    return 0;
}

#include "QWheelEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

// http://qt-project.org/doc/qt-5/qwheelevent.html

namespace lua {

void QWheelEvent_metatable(lua_State* const state, const int pos)
{
    lua::QInputEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["angleDelta"] = &QWheelEvent::angleDelta;
    mt["buttons"] = &QWheelEvent::buttons;
    mt["globalPos"] = &QWheelEvent::globalPos;
    mt["globalPosF"] = &QWheelEvent::globalPosF;
    mt["globalX"] = &QWheelEvent::globalX;
    mt["globalY"] = &QWheelEvent::globalY;
    mt["phase"] = &QWheelEvent::phase;
    mt["pixelDelta"] = &QWheelEvent::pixelDelta;
    mt["pos"] = &QWheelEvent::pos;
    mt["posF"] = &QWheelEvent::posF;
    mt["x"] = &QWheelEvent::x;
    mt["y"] = &QWheelEvent::y;
}

} // namespace lua

int QWheelEvent_new(lua_State* const state)
{
    if (lua_gettop(state) == 8) {
        // QWheelEvent(const QPointF & pos, const QPointF & globalPos, QPoint pixelDelta, QPoint angleDelta, int qt4Delta, Qt::Orientation qt4Orientation, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers)
        lua::make<QWheelEvent>(state,
            lua::get<const QPointF&>(state, 1),
            lua::get<const QPointF&>(state, 2),
            lua::get<QPoint>(state, 3),
            lua::get<QPoint>(state, 4),
            lua::get<int>(state, 5),
            lua::get<Qt::Orientation>(state, 6),
            lua::get<Qt::MouseButtons>(state, 7),
            lua::get<Qt::KeyboardModifiers>(state, 8)
        );
    } else {
        // QWheelEvent(const QPointF & pos, const QPointF & globalPos, QPoint pixelDelta, QPoint angleDelta, int qt4Delta, Qt::Orientation qt4Orientation, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers, Qt::ScrollPhase phase)
        lua::make<QWheelEvent>(state,
            lua::get<const QPointF&>(state, 1),
            lua::get<const QPointF&>(state, 2),
            lua::get<QPoint>(state, 3),
            lua::get<QPoint>(state, 4),
            lua::get<int>(state, 5),
            lua::get<Qt::Orientation>(state, 6),
            lua::get<Qt::MouseButtons>(state, 7),
            lua::get<Qt::KeyboardModifiers>(state, 8),
            lua::get<Qt::ScrollPhase>(state, 9)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QWheelEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QWheelEvent"] = lua::value::table;
    env["QWheelEvent"]["new"] = QWheelEvent_new;
    auto t = env["QWheelEvent"];

    return 0;
}

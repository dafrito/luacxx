#include "QTouchEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QWindow.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "QTouchDevice.hpp"

namespace lua {

void QTouchEvent_metatable(lua_State* const state, const int pos)
{
    lua::QInputEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["device"] = &QTouchEvent::device;
    mt["target"] = &QTouchEvent::target;
    mt["touchPointStates"] = &QTouchEvent::touchPointStates;
    // FIXME (QList type does not implement operator==) mt["touchPoints"] = &QTouchEvent::touchPoints;
    mt["window"] = &QTouchEvent::window;
}

} // namespace lua

int QTouchEvent_new(lua_State* const state)
{
    // QTouchEvent(QEvent::Type eventType, QTouchDevice * device = 0, Qt::KeyboardModifiers modifiers = Qt::NoModifier, Qt::TouchPointStates touchPointStates = 0, const QList<QTouchEvent::TouchPoint> & touchPoints = QList<QTouchEvent::TouchPoint> ())
    switch (lua_gettop(state)) {
    case 1:
        lua::make<QTouchEvent>(state,
            lua::get<QEvent::Type>(state, 1)
        );
        break;
    case 2:
        lua::make<QTouchEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<QTouchDevice*>(state, 2)
        );
        break;
    case 3:
        lua::make<QTouchEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<QTouchDevice*>(state, 2),
            lua::get<Qt::KeyboardModifiers>(state, 3)
        );
        break;
    case 4:
        lua::make<QTouchEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<QTouchDevice*>(state, 2),
            lua::get<Qt::KeyboardModifiers>(state, 3),
            lua::get<Qt::TouchPointStates>(state, 4)
        );
        break;
    case 5:
    default:
        lua::make<QTouchEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<QTouchDevice*>(state, 2),
            lua::get<Qt::KeyboardModifiers>(state, 3),
            lua::get<Qt::TouchPointStates>(state, 4),
            lua::get<const QList<QTouchEvent::TouchPoint>&>(state, 5)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Gui_QTouchEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QTouchEvent"] = lua::value::table;
    env["QTouchEvent"]["new"] = QTouchEvent_new;
    auto t = env["QTouchEvent"];

    return 0;
}

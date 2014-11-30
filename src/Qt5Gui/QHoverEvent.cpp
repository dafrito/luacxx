#include "QHoverEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/Qt.hpp"

// http://qt-project.org/doc/qt-5/qhoverevent.html

namespace lua {

void QHoverEvent_metatable(lua_State* const state, const int pos)
{
    lua::QInputEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["oldPos"] = &QHoverEvent::oldPos;
    mt["oldPosF"] = &QHoverEvent::oldPosF;
    mt["pos"] = &QHoverEvent::pos;
    mt["posF"] = &QHoverEvent::posF;
}

} // namespace lua

int QHoverEvent_new(lua_State* const state)
{
    // QHoverEvent(Type type, const QPointF & pos, const QPointF & oldPos, Qt::KeyboardModifiers modifiers = Qt::NoModifier)
    if (lua_gettop(state) == 4) {
        lua::make<QHoverEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<const QPointF&>(state, 2),
            lua::get<const QPointF&>(state, 3)
        );
    } else {
        lua::make<QHoverEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<const QPointF&>(state, 2),
            lua::get<const QPointF&>(state, 3),
            lua::get<Qt::KeyboardModifiers>(state, 4)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QHoverEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QHoverEvent"] = lua::value::table;
    env["QHoverEvent"]["new"] = QHoverEvent_new;
    auto t = env["QHoverEvent"];

    return 0;
}

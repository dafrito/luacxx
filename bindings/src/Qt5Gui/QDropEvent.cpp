#include "QDropEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QMimeData.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QPoint.hpp"

// http://qt-project.org/doc/qt-5/qdropevent.html

namespace lua {

void QDropEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["acceptProposedAction"] = &QDropEvent::acceptProposedAction;
    mt["dropAction"] = &QDropEvent::dropAction;
    mt["keyboardModifiers"] = &QDropEvent::keyboardModifiers;
    mt["mimeData"] = &QDropEvent::mimeData;
    mt["mouseButtons"] = &QDropEvent::mouseButtons;
    mt["pos"] = &QDropEvent::pos;
    mt["posF"] = &QDropEvent::posF;
    mt["possibleActions"] = &QDropEvent::possibleActions;
    mt["proposedAction"] = &QDropEvent::proposedAction;
    mt["setDropAction"] = &QDropEvent::setDropAction;
    mt["source"] = &QDropEvent::source;
}

} // namespace lua

int QDropEvent_new(lua_State* const state)
{
    // QDropEvent(const QPointF & pos, Qt::DropActions actions, const QMimeData * data, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers, Type type = Drop)
    if (lua_gettop(state) == 5) {
        lua::make<QDropEvent>(state,
            lua::get<const QPointF&>(state, 1),
            lua::get<Qt::DropActions>(state, 2),
            lua::get<const QMimeData*>(state, 3),
            lua::get<Qt::MouseButtons>(state, 4),
            lua::get<Qt::KeyboardModifiers>(state, 5)
        );
    } else {
        lua::make<QDropEvent>(state,
            lua::get<const QPointF&>(state, 1),
            lua::get<Qt::DropActions>(state, 2),
            lua::get<const QMimeData*>(state, 3),
            lua::get<Qt::MouseButtons>(state, 4),
            lua::get<Qt::KeyboardModifiers>(state, 5),
            lua::get<QEvent::Type>(state, 6)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QDropEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QDropEvent"] = lua::value::table;
    env["QDropEvent"]["new"] = QDropEvent_new;
    auto t = env["QDropEvent"];

    return 0;
}

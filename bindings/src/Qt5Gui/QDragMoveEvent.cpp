#include "QDragMoveEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QMimeData.hpp"

// http://qt-project.org/doc/qt-5/qdragmoveevent.html

int QDragMoveEvent_accept(lua_State* const state)
{
    auto self = lua::get<QDragMoveEvent*>(state, 1);

    if (lua_gettop(state) == 1) {
        self->accept();
    } else {
        self->accept(
            lua::get<const QRect&>(state, 2)
        );
    }

    return 1;
}
int QDragMoveEvent_ignore(lua_State* const state)
{
    auto self = lua::get<QDragMoveEvent*>(state, 1);

    if (lua_gettop(state) == 1) {
        self->ignore();
    } else {
        self->ignore(
            lua::get<const QRect&>(state, 2)
        );
    }

    return 1;
}

namespace lua {

void QDragMoveEvent_metatable(lua_State* const state, const int pos)
{
    lua::QDropEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["accept"] = QDragMoveEvent_accept;
    mt["answerRect"] = &QDragMoveEvent::answerRect;
    mt["ignore"] = QDragMoveEvent_ignore;
}

} // namespace lua

int QDragMoveEvent_new(lua_State* const state)
{
    // QDragMoveEvent(const QPoint & pos, Qt::DropActions actions, const QMimeData * data, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers, Type type = DragMove)
    if (lua_gettop(state) == 5) {
        lua::make<QDragMoveEvent>(state,
            lua::get<const QPoint&>(state, 1),
            lua::get<Qt::DropActions>(state, 2),
            lua::get<const QMimeData*>(state, 3),
            lua::get<Qt::MouseButtons>(state, 4),
            lua::get<Qt::KeyboardModifiers>(state, 5)
        );
    } else {
        lua::make<QDragMoveEvent>(state,
            lua::get<const QPoint&>(state, 1),
            lua::get<Qt::DropActions>(state, 2),
            lua::get<const QMimeData*>(state, 3),
            lua::get<Qt::MouseButtons>(state, 4),
            lua::get<Qt::KeyboardModifiers>(state, 5),
            lua::get<QEvent::Type>(state, 6)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QDragMoveEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QDragMoveEvent"] = lua::value::table;
    env["QDragMoveEvent"]["new"] = QDragMoveEvent_new;
    auto t = env["QDragMoveEvent"];

    return 0;
}

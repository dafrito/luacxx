#include "QDragEnterEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QMimeData.hpp"

// http://qt-project.org/doc/qt-5/qdragenterevent.html

namespace lua {

void QDragEnterEvent_metatable(lua_State* const state, const int pos)
{
    lua::QDragMoveEvent_metatable(state, pos);
}

} // namespace lua

int QDragEnterEvent_new(lua_State* const state)
{
    // QDragEnterEvent(const QPoint & point, Qt::DropActions actions, const QMimeData * data, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers)
    lua::make<QDragEnterEvent>(state,
        lua::get<const QPoint&>(state, 1),
        lua::get<Qt::DropActions>(state, 2),
        lua::get<const QMimeData*>(state, 3),
        lua::get<Qt::MouseButtons>(state, 4),
        lua::get<Qt::KeyboardModifiers>(state, 5)
    );

    return 1;
}

int luaopen_Qt5Gui_QDragEnterEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QDragEnterEvent"] = lua::value::table;
    env["QDragEnterEvent"]["new"] = QDragEnterEvent_new;
    auto t = env["QDragEnterEvent"];

    return 0;
}

#include "QDrag.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QPixmap.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QMimeData.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

#include <QDrag>

// Qt::DropAction     exec(Qt::DropActions supportedActions = Qt::MoveAction)
// Qt::DropAction     exec(Qt::DropActions supportedActions, Qt::DropAction defaultDropAction)
int QDrag_exec(lua_State* const state)
{
    auto self = lua::get<QDrag*>(state, 1);
    switch (lua_gettop(state)) {
        case 1:
            lua::push(state, self->exec());
            break;
        case 2:
            lua::push(state, self->exec(
                lua::get<Qt::DropActions>(state, 2)
            ));
            break;
        case 3:
        default:
            lua::push(state, self->exec(
                lua::get<Qt::DropActions>(state, 2),
                lua::get<Qt::DropAction>(state, 2)
            ));
            break;
    }
    return 1;
}

void lua::QDrag_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["defaultAction"] = &QDrag::defaultAction;
    mt["dragCursor"] = &QDrag::dragCursor;
    mt["exec"] = QDrag_exec;
    mt["hotSpot"] = &QDrag::hotSpot;
    mt["mimeData"] = &QDrag::mimeData;
    mt["pixmap"] = &QDrag::pixmap;
    mt["setDragCursor"] = &QDrag::setDragCursor;
    mt["setHotSpot"] = &QDrag::setHotSpot;
    mt["setMimeData"] = &QDrag::setMimeData;
    mt["setPixmap"] = &QDrag::setPixmap;
    mt["source"] = &QDrag::source;
    mt["supportedActions"] = &QDrag::supportedActions;
    mt["target"] = &QDrag::target;
}

int QDrag_new(lua_State* const state)
{
    lua::make<QDrag>(state, lua::get<QObject*>(state, 2));
    return 1;
}

int luaopen_Qt5Gui_QDrag(lua_State* const state)
{
    lua::thread env(state);

    env["QDrag"] = lua::value::table;
    env["QDrag"]["new"] = QDrag_new;

    return 0;
}

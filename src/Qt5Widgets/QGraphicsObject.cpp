#include "QGraphicsObject.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QObject.hpp"
#include "QGraphicsItem.hpp"

#include <QGraphicsObject>

int QGraphicsItem_grabGesture(lua_State* const state)
{
    return 0;
}

void lua::QGraphicsObject_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);
    lua::QGraphicsItem_metatable(mt);

    mt["grabGesture"] = QGraphicsItem_grabGesture;
    mt["ungrabGesture"] = &QGraphicsObject::ungrabGesture;
}

int luaopen_Qt5Widgets_QGraphicsObject(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsObject"] = lua::value::table;

    return 0;
}

#ifndef luacxx_QGraphicsPathItem_INCLUDED
#define luacxx_QGraphicsPathItem_INCLUDED

#include "../stack.hpp"

#include <QGraphicsPathItem>

#include "QAbstractGraphicsShapeItem.hpp"

// https://qt-project.org/doc/qt-5/qgraphicspathitem.html

LUA_METATABLE_INHERIT(QGraphicsPathItem, QAbstractGraphicsShapeItem)

extern "C" int luaopen_Qt5Widgets_QGraphicsPathItem(lua_State* const);

#endif // luacxx_QGraphicsPathItem_INCLUDED

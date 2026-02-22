#ifndef luacxx_QGraphicsPolygonItem_INCLUDED
#define luacxx_QGraphicsPolygonItem_INCLUDED

#include "../stack.hpp"

#include <QGraphicsPolygonItem>

#include "QAbstractGraphicsShapeItem.hpp"

// https://qt-project.org/doc/qt-5/qgraphicspolygonitem.html

LUA_METATABLE_INHERIT(QGraphicsPolygonItem, QAbstractGraphicsShapeItem)

extern "C" int luaopen_Qt5Widgets_QGraphicsPolygonItem(lua_State* const);

#endif // luacxx_QGraphicsPolygonItem_INCLUDED

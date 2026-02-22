#ifndef luacxx_QGraphicsEllipseItem_INCLUDED
#define luacxx_QGraphicsEllipseItem_INCLUDED

#include "../stack.hpp"

#include <QGraphicsEllipseItem>

#include "QAbstractGraphicsShapeItem.hpp"

// https://qt-project.org/doc/qt-5/qgraphicsellipseitem.html

LUA_METATABLE_INHERIT(QGraphicsEllipseItem, QAbstractGraphicsShapeItem)

extern "C" int luaopen_Qt5Widgets_QGraphicsEllipseItem(lua_State* const);

#endif // luacxx_QGraphicsEllipseItem_INCLUDED

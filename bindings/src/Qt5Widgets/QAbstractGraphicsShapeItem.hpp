#ifndef luacxx_QAbstractGraphicsShapeItem_INCLUDED
#define luacxx_QAbstractGraphicsShapeItem_INCLUDED

#include "../stack.hpp"

#include <QAbstractGraphicsShapeItem>

#include "QGraphicsItem.hpp"

// https://qt-project.org/doc/qt-5/qabstractgraphicsshapeitem.html

LUA_METATABLE_INHERIT(QAbstractGraphicsShapeItem, QGraphicsItem)

#endif // luacxx_QAbstractGraphicsShapeItem_INCLUDED

#ifndef luacxx_QGraphicsRectItem_INCLUDED
#define luacxx_QGraphicsRectItem_INCLUDED

#include "../stack.hpp"

#include <QGraphicsRectItem>

#include "QAbstractGraphicsShapeItem.hpp"

LUA_METATABLE_INHERIT(QGraphicsRectItem, QAbstractGraphicsShapeItem)

extern "C" int luaopen_Qt5Widgets_QGraphicsRectItem(lua_State* const);

#endif // luacxx_QGraphicsRectItem_INCLUDED

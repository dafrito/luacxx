#ifndef luacxx_QGraphicsPixmapItem_INCLUDED
#define luacxx_QGraphicsPixmapItem_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QGraphicsPixmapItem>

#include "QGraphicsItem.hpp"

LUA_METATABLE_INHERIT(QGraphicsPixmapItem, QGraphicsItem)
LUA_METATABLE_ENUM(QGraphicsPixmapItem::ShapeMode)

extern "C" int luaopen_Qt5Widgets_QGraphicsPixmapItem(lua_State* const);

#endif // luacxx_QGraphicsPixmapItem_INCLUDED

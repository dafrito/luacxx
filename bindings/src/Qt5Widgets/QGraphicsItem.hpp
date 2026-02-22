#ifndef LUA_CXX_QGRAPHICSITEM_INCLUDED
#define LUA_CXX_QGRAPHICSITEM_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QGraphicsItem>

LUA_METATABLE_BUILT(QGraphicsItem);
LUA_METATABLE_ENUM(QGraphicsItem::CacheMode);
LUA_METATABLE_ENUM(QGraphicsItem::GraphicsItemChange);
LUA_METATABLE_ENUM(QGraphicsItem::GraphicsItemFlag);
LUA_METATABLE_ENUM(QGraphicsItem::PanelModality);

extern "C" int luaopen_Qt5Widgets_QGraphicsItem(lua_State* const);

#endif // LUA_CXX_QGRAPHICSITEM_INCLUDED

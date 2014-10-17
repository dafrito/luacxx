#ifndef LUA_CXX_QGRAPHICSITEM_INCLUDED
#define LUA_CXX_QGRAPHICSITEM_INCLUDED

#include "Qt5Widgets.hpp"

#include <QGraphicsItem>

LUA_METATABLE_BUILT(QGraphicsItem);

extern "C" int luaopen_Qt5Widgets_QGraphicsItem(lua_State* const);

#endif // LUA_CXX_QGRAPHICSITEM_INCLUDED

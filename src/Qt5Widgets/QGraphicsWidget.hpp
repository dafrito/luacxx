#ifndef LUA_CXX_QGRAPHICSWIDGET_INCLUDED
#define LUA_CXX_QGRAPHICSWIDGET_INCLUDED

#include "Qt5Widgets.hpp"

class QGraphicsWidget;

LUA_METATABLE_BUILT(QGraphicsWidget);

extern "C" int luaopen_Qt5Widgets_QGraphicsWidget(lua_State* const);

#endif // LUA_CXX_QGRAPHICSWIDGET_INCLUDED

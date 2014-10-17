#ifndef LUA_CXX_QGRAPHICSVIEW_INCLUDED
#define LUA_CXX_QGRAPHICSVIEW_INCLUDED

#include "Qt5Widgets.hpp"

#include <QGraphicsView>

LUA_METATABLE_BUILT(QGraphicsView);

extern "C" int luaopen_Qt5Widgets_QGraphicsView(lua_State* const);

#endif // LUA_CXX_QGRAPHICSVIEW_INCLUDED

#ifndef LUA_CXX_QGRAPHICSVIEW_INCLUDED
#define LUA_CXX_QGRAPHICSVIEW_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QGraphicsView>

LUA_METATABLE_BUILT(QGraphicsView);
LUA_METATABLE_ENUM(QGraphicsView::CacheModeFlag);
LUA_METATABLE_ENUM(QGraphicsView::DragMode);
LUA_METATABLE_ENUM(QGraphicsView::OptimizationFlag);
LUA_METATABLE_ENUM(QGraphicsView::ViewportAnchor);
LUA_METATABLE_ENUM(QGraphicsView::ViewportUpdateMode);

extern "C" int luaopen_Qt5Widgets_QGraphicsView(lua_State* const);

#endif // LUA_CXX_QGRAPHICSVIEW_INCLUDED

#ifndef LUA_CXX_QGRAPHICSVIEW_INCLUDED
#define LUA_CXX_QGRAPHICSVIEW_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QGraphicsView>

#include "QAbstractScrollArea.hpp"

// http://qt-project.org/doc/qt-5/qgraphicsview.html

LUA_METATABLE_INHERIT(QGraphicsView, QAbstractScrollArea);

LUA_METATABLE_ENUM(QGraphicsView::CacheModeFlag);
LUA_METATABLE_ENUM(QGraphicsView::DragMode);
LUA_METATABLE_ENUM(QGraphicsView::OptimizationFlag);
LUA_METATABLE_ENUM(QGraphicsView::ViewportAnchor);
LUA_METATABLE_ENUM(QGraphicsView::ViewportUpdateMode);

extern "C" int luaopen_Qt5Widgets_QGraphicsView(lua_State* const);

#endif // LUA_CXX_QGRAPHICSVIEW_INCLUDED

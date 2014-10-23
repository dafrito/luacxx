#ifndef LUA_CXX_QDOCKWIDGET_INCLUDED
#define LUA_CXX_QDOCKWIDGET_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QDockWidget>

LUA_METATABLE_BUILT(QDockWidget);
LUA_METATABLE_ENUM(QDockWidget::DockWidgetFeature);

extern "C" int luaopen_Qt5Widgets_QDockWidget(lua_State* const);

#endif // LUA_CXX_QDOCKWIDGET_INCLUDED

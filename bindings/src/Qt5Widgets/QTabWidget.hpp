#ifndef LUA_CXX_QTABWIDGET_INCLUDED
#define LUA_CXX_QTABWIDGET_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QTabWidget>

LUA_METATABLE_BUILT(QTabWidget);
LUA_METATABLE_ENUM(QTabWidget::TabPosition);
LUA_METATABLE_ENUM(QTabWidget::TabShape);

extern "C" int luaopen_Qt5Widgets_QTabWidget(lua_State* const);

#endif // LUA_CXX_QTABWIDGET_INCLUDED

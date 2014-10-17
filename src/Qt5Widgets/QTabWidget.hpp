#ifndef LUA_CXX_QTABWIDGET_INCLUDED
#define LUA_CXX_QTABWIDGET_INCLUDED

#include "Qt5Widgets.hpp"

class QTabWidget;

LUA_METATABLE_BUILT(QTabWidget);

extern "C" int luaopen_Qt5Widgets_QTabWidget(lua_State* const);

#endif // LUA_CXX_QTABWIDGET_INCLUDED

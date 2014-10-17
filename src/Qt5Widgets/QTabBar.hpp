#ifndef LUA_CXX_QTABBAR_INCLUDED
#define LUA_CXX_QTABBAR_INCLUDED

#include "Qt5Widgets.hpp"

class QTabBar;

LUA_METATABLE_BUILT(QTabBar);

extern "C" int luaopen_Qt5Widgets_QTabBar(lua_State* const);

#endif // LUA_CXX_QTABBAR_INCLUDED

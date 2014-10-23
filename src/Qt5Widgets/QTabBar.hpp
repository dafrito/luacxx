#ifndef LUA_CXX_QTABBAR_INCLUDED
#define LUA_CXX_QTABBAR_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QTabBar>

LUA_METATABLE_BUILT(QTabBar);
LUA_METATABLE_ENUM(QTabBar::ButtonPosition);
LUA_METATABLE_ENUM(QTabBar::SelectionBehavior);
LUA_METATABLE_ENUM(QTabBar::Shape);

extern "C" int luaopen_Qt5Widgets_QTabBar(lua_State* const);

#endif // LUA_CXX_QTABBAR_INCLUDED

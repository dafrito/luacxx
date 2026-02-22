#ifndef LUA_CXX_QMAINWINDOW_INCLUDED
#define LUA_CXX_QMAINWINDOW_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QMainWindow>

LUA_METATABLE_BUILT(QMainWindow);
LUA_METATABLE_ENUM(QMainWindow::DockOption);

extern "C" int luaopen_Qt5Widgets_QMainWindow(lua_State* const);

#endif // LUA_CXX_QMAINWINDOW_INCLUDED

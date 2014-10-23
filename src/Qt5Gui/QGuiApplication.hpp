#ifndef LUACXX_QGUIAPPLICATION_INCLUDED
#define LUACXX_QGUIAPPLICATION_INCLUDED

#include "Qt5Gui.hpp"

#include <QGuiApplication>
#include <QStyleHints>

LUA_METATABLE_BUILT(QGuiApplication);
LUA_METATABLE_BUILT(QStyleHints);

extern "C" int luaopen_Qt5Gui_QGuiApplication(lua_State* const);

#endif // LUACXX_QGUIAPPLICATION_INCLUDED

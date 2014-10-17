#ifndef LUACXX_QGUIAPPLICATION_INCLUDED
#define LUACXX_QGUIAPPLICATION_INCLUDED

#include "Qt5Gui.hpp"

#include <QGuiApplication>

LUA_METATABLE_BUILT(QGuiApplication);

extern "C" int luaopen_Qt5Gui_QGuiApplication(lua_State* const);

#endif // LUACXX_QGUIAPPLICATION_INCLUDED

#ifndef LUACXX_QPALETTE_INCLUDED
#define LUACXX_QPALETTE_INCLUDED

#include "Qt5Gui.hpp"
#include <QPalette>

// http://qt-project.org/doc/qt-5/qpalette.html

LUA_METATABLE_BUILT(QPalette);

extern "C" int luaopen_Qt5Gui_QPalette(lua_State* const);

#endif // LUACXX_QPALETTE_INCLUDED

#ifndef LUACXX_QPAINTER_INCLUDED
#define LUACXX_QPAINTER_INCLUDED

#include "Qt5Gui.hpp"
#include <QPainter>

LUA_METATABLE_BUILT(QPainter);

extern "C" int luaopen_Qt5Gui_QPainter(lua_State* const);

#endif // LUACXX_QPAINTER_INCLUDED

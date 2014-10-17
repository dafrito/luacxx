#ifndef LUACXX_QPEN_INCLUDED
#define LUACXX_QPEN_INCLUDED

#include "Qt5Gui.hpp"
#include <QPen>

LUA_METATABLE_BUILT(QPen);

extern "C" int luaopen_Qt5Gui_QPen(lua_State* const);

#endif // LUACXX_QPEN_INCLUDED

#ifndef LUACXX_QBRUSH_INCLUDED
#define LUACXX_QBRUSH_INCLUDED

#include "Qt5Gui.hpp"

#include <QBrush>

LUA_METATABLE_BUILT(QBrush);

extern "C" int luaopen_Qt5Gui_QBrush(lua_State* const);

#endif // LUACXX_QBRUSH_INCLUDED

#ifndef LUACXX_QBITMAP_INCLUDED
#define LUACXX_QBITMAP_INCLUDED

#include "Qt5Gui.hpp"

#include <QBitmap>

LUA_METATABLE_BUILT(QBitmap);

extern "C" int luaopen_Qt5Gui_QBitmap(lua_State* const);

#endif // LUACXX_QBITMAP_INCLUDED

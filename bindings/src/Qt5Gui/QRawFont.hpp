#ifndef LUACXX_QRAWFONT_INCLUDED
#define LUACXX_QRAWFONT_INCLUDED

#include "Qt5Gui.hpp"
#include <QRawFont>

LUA_METATABLE_BUILT(QRawFont);

extern "C" int luaopen_Qt5Gui_QRawFont(lua_State* const);

#endif // LUACXX_QRAWFONT_INCLUDED

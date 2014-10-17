#ifndef LUACXX_QFONT_INCLUDED
#define LUACXX_QFONT_INCLUDED

#include "Qt5Gui.hpp"
#include <QFont>

LUA_METATABLE_BUILT(QFont);

extern "C" int luaopen_Qt5Gui_QFont(lua_State* const);

#endif // LUACXX_QFONT_INCLUDED

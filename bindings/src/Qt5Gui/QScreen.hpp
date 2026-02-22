#ifndef LUACXX_QSCREEN_INCLUDED
#define LUACXX_QSCREEN_INCLUDED

#include "Qt5Gui.hpp"
#include <QScreen>

LUA_METATABLE_BUILT(QScreen);

extern "C" int luaopen_Qt5Gui_QScreen(lua_State* const);

#endif // LUACXX_QSCREEN_INCLUDED

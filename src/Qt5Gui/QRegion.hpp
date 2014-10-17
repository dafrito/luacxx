#ifndef LUACXX_QREGION_INCLUDED
#define LUACXX_QREGION_INCLUDED

#include "Qt5Gui.hpp"
#include <QRegion>

LUA_METATABLE_BUILT(QRegion);

extern "C" int luaopen_Qt5Gui_QRegion(lua_State* const);

#endif // LUACXX_QREGION_INCLUDED

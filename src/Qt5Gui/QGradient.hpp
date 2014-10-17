#ifndef LUACXX_QGRADIENT_INCLUDED
#define LUACXX_QGRADIENT_INCLUDED

#include "Qt5Gui.hpp"

class QGradient;

LUA_METATABLE_BUILT(QGradient);

extern "C" int luaopen_Qt5Gui_QGradient(lua_State* const);

#endif // LUACXX_QGRADIENT_INCLUDED

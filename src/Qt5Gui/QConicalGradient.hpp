#ifndef LUACXX_QCONICALGRADIENT_INCLUDED
#define LUACXX_QCONICALGRADIENT_INCLUDED

#include "Qt5Gui.hpp"

class QConicalGradient;

LUA_METATABLE_BUILT(QConicalGradient);

extern "C" int luaopen_Qt5Gui_QConicalGradient(lua_State* const);

#endif // LUACXX_QCONICALGRADIENT_INCLUDED

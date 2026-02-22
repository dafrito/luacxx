#ifndef LUACXX_QCONICALGRADIENT_INCLUDED
#define LUACXX_QCONICALGRADIENT_INCLUDED

#include "Qt5Gui.hpp"

#include <QConicalGradient>

#include "QGradient.hpp"

LUA_METATABLE_INHERIT(QConicalGradient, QGradient);

extern "C" int luaopen_Qt5Gui_QConicalGradient(lua_State* const);

#endif // LUACXX_QCONICALGRADIENT_INCLUDED

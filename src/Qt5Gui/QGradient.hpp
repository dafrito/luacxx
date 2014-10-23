#ifndef LUACXX_QGRADIENT_INCLUDED
#define LUACXX_QGRADIENT_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QGradient>

LUA_METATABLE_BUILT(QGradient);
LUA_METATABLE_ENUM(QGradient::CoordinateMode);
LUA_METATABLE_ENUM(QGradient::Spread);
LUA_METATABLE_ENUM(QGradient::Type);

extern "C" int luaopen_Qt5Gui_QGradient(lua_State* const);

#endif // LUACXX_QGRADIENT_INCLUDED

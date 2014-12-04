#ifndef LUACXX_QLINEARGRADIENT_INCLUDED
#define LUACXX_QLINEARGRADIENT_INCLUDED

#include "Qt5Gui.hpp"

#include <QLinearGradient>

#include "QGradient.hpp"

LUA_METATABLE_INHERIT(QLinearGradient, QGradient);

extern "C" int luaopen_Qt5Gui_QLinearGradient(lua_State* const);

#endif // LUACXX_QLINEARGRADIENT_INCLUDED

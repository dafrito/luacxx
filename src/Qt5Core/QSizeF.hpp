#ifndef LUACXX_QSIZEF_INCLUDED
#define LUACXX_QSIZEF_INCLUDED

#include "Qt5Core.hpp"

#include <QSizeF>

LUA_METATABLE_BUILT(QSizeF)

extern "C" int luaopen_Qt5Core_QSizeF(lua_State* const);

#endif // LUACXX_QSIZEF_INCLUDED

#ifndef LUACXX_QPOINT_INCLUDED
#define LUACXX_QPOINT_INCLUDED

#include "Qt5Core.hpp"

#include <QPoint>

LUA_METATABLE_BUILT(QPoint)

extern "C" int luaopen_Qt5Core_QPoint(lua_State* const);

#endif // LUACXX_QPOINT_INCLUDED

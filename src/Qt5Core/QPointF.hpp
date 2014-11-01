#ifndef LUACXX_QPOINTF_INCLUDED
#define LUACXX_QPOINTF_INCLUDED

#include "Qt5Core.hpp"

#include <QPointF>

LUA_METATABLE_BUILT(QPointF)

extern "C" int luaopen_Qt5Core_QPointF(lua_State* const);

#endif // LUACXX_QPOINTF_INCLUDED

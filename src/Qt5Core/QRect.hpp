#ifndef LUACXX_QRECT_INCLUDED
#define LUACXX_QRECT_INCLUDED

#include "Qt5Core.hpp"

#include <QRect>

class QRect;

LUA_METATABLE_BUILT(QRect)

extern "C" int luaopen_Qt5Core_QRect(lua_State* const);

#endif // LUACXX_QRECT_INCLUDED

#ifndef LUACXX_QRECTF_INCLUDED
#define LUACXX_QRECTF_INCLUDED

#include "Qt5Core.hpp"

class QRectF;

LUA_METATABLE_BUILT(QRectF)

extern "C" int luaopen_Qt5Core_QRectF(lua_State* const);

#endif // LUACXX_QRECTF_INCLUDED

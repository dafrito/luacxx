#ifndef LUACXX_QELAPSEDTIMER_INCLUDED
#define LUACXX_QELAPSEDTIMER_INCLUDED

#include "Qt5Core.hpp"

class QElapsedTimer;

LUA_METATABLE_BUILT(QElapsedTimer)

extern "C" int luaopen_Qt5Core_QElapsedTimer(lua_State* const);

#endif // LUACXX_QELAPSEDTIMER_INCLUDED

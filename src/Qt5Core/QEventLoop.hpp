#ifndef LUACXX_QEVENTLOOP_INCLUDED
#define LUACXX_QEVENTLOOP_INCLUDED

#include "Qt5Core.hpp"

class QEventLoop;

LUA_METATABLE_BUILT(QEventLoop)

extern "C" int luaopen_Qt5Core_QEventLoop(lua_State* const);

#endif // LUACXX_QEVENTLOOP_INCLUDED

#ifndef LUACXX_QEVENTLOOP_INCLUDED
#define LUACXX_QEVENTLOOP_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include <QEventLoop>

LUA_METATABLE_BUILT(QEventLoop)
LUA_METATABLE_ENUM(QEventLoop::ProcessEventsFlag)

extern "C" int luaopen_Qt5Core_QEventLoop(lua_State* const);

#endif // LUACXX_QEVENTLOOP_INCLUDED

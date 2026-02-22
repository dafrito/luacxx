#ifndef luacxx_QAbstractEventDispatcher_INCLUDED
#define luacxx_QAbstractEventDispatcher_INCLUDED

#include "../stack.hpp"

#include <QAbstractEventDispatcher>

LUA_METATABLE_BUILT(QAbstractEventDispatcher)
LUA_METATABLE_NAMED(QAbstractEventDispatcher::TimerInfo)

extern "C" int luaopen_Qt5Core_QAbstractEventDispatcher(lua_State* const);

#endif // luacxx_QAbstractEventDispatcher_INCLUDED

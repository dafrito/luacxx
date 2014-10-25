#ifndef luacxx_QThread_INCLUDED
#define luacxx_QThread_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QThread>

LUA_METATABLE_BUILT(QThread)
LUA_METATABLE_ENUM(QThread::Priority)

extern "C" int luaopen_Qt5Core_QThread(lua_State* const);

#endif // luacxx_QThread_INCLUDED

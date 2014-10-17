#ifndef luacxx_QTime_INCLUDED
#define luacxx_QTime_INCLUDED

#include "Qt5Core.hpp"

#include <QTime>

LUA_METATABLE_BUILT(QTime)

extern "C" int luaopen_luacxx_QTime(lua_State* const);

#endif // luacxx_QTime_INCLUDED

#ifndef LUACXX_QSIZE_INCLUDED
#define LUACXX_QSIZE_INCLUDED

#include "Qt5Core.hpp"

class QSize;

LUA_METATABLE_BUILT(QSize)

extern "C" int luaopen_Qt5Core_QSize(lua_State* const);

#endif // LUACXX_QSIZE_INCLUDED

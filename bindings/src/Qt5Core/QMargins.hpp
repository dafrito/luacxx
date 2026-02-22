#ifndef LUA_CXX_QMARGINS_INCLUDED
#define LUA_CXX_QMARGINS_INCLUDED

#include "Qt5Core.hpp"

class QMargins;

LUA_METATABLE_BUILT(QMargins)

extern "C" int luaopen_Qt5Core_QMargins(lua_State* const);

#endif // LUA_CXX_QMARGINS_INCLUDED

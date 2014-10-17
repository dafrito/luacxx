#ifndef luacxx_QHostAddress_INCLUDED
#define luacxx_QHostAddress_INCLUDED

#include "Qt5Network.hpp"

class QHostAddress;

LUA_METATABLE_BUILT(QHostAddress);

extern "C" int luaopen_luacxx_QHostAddress(lua_State* const);

#endif // luacxx_QHostAddress_INCLUDED

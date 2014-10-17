#ifndef luacxx_QCryptographicHash_INCLUDED
#define luacxx_QCryptographicHash_INCLUDED

#include "Qt5Core.hpp"

class QCryptographicHash;

LUA_METATABLE_BUILT(QCryptographicHash)

extern "C" int luaopen_Qt5Core_QCryptographicHash(lua_State* const);

#endif // luacxx_QCryptographicHash_INCLUDED

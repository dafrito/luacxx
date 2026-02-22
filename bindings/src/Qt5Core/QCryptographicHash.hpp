#ifndef luacxx_QCryptographicHash_INCLUDED
#define luacxx_QCryptographicHash_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include <QCryptographicHash>

LUA_METATABLE_BUILT(QCryptographicHash)
LUA_METATABLE_ENUM(QCryptographicHash::Algorithm);

extern "C" int luaopen_Qt5Core_QCryptographicHash(lua_State* const);

#endif // luacxx_QCryptographicHash_INCLUDED

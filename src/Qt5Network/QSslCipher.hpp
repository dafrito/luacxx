#ifndef luacxx_QSslCipher_INCLUDED
#define luacxx_QSslCipher_INCLUDED

#include "Qt5Network.hpp"

#include <QSslCipher>

LUA_METATABLE_BUILT(QSslCipher);

extern "C" int luaopen_luacxx_QSslCipher(lua_State* const);

#endif // luacxx_QSslCipher_INCLUDED

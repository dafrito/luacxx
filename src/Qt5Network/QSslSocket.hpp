#ifndef luacxx_QSslSocket_INCLUDED
#define luacxx_QSslSocket_INCLUDED

#include "../stack.hpp"

#include <QSslSocket>

LUA_METATABLE_BUILT(QSslSocket);

extern "C" int luaopen_luacxx_QSslSocket(lua_State* const);

#endif // luacxx_QSslSocket_INCLUDED

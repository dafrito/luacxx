#ifndef luacxx_QSslSocket_INCLUDED
#define luacxx_QSslSocket_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QSslSocket>

LUA_METATABLE_BUILT(QSslSocket);
LUA_METATABLE_ENUM(QSslSocket::PeerVerifyMode);
LUA_METATABLE_ENUM(QSslSocket::SslMode);

extern "C" int luaopen_luacxx_QSslSocket(lua_State* const);

#endif // luacxx_QSslSocket_INCLUDED

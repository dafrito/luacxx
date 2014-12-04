#ifndef luacxx_QSslSocket_INCLUDED
#define luacxx_QSslSocket_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QSslSocket>

#include "QAbstractSocket.hpp"

LUA_METATABLE_INHERIT(QSslSocket, QAbstractSocket);
LUA_METATABLE_ENUM(QSslSocket::PeerVerifyMode);
LUA_METATABLE_ENUM(QSslSocket::SslMode);

extern "C" int luaopen_Qt5Network_QSslSocket(lua_State* const);

#endif // luacxx_QSslSocket_INCLUDED

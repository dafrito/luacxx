#ifndef LUACXX_QABSTRACTSOCKET_INCLUDED
#define LUACXX_QABSTRACTSOCKET_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QAbstractSocket>

#include "../Qt5Core/QIODevice.hpp"

// http://qt-project.org/doc/qt-5/qabstractsocket.html

LUA_METATABLE_INHERIT(QAbstractSocket, QIODevice);
LUA_METATABLE_ENUM(QAbstractSocket::BindFlag);
LUA_METATABLE_ENUM(QAbstractSocket::NetworkLayerProtocol);
LUA_METATABLE_ENUM(QAbstractSocket::PauseMode);
LUA_METATABLE_ENUM(QAbstractSocket::SocketError);
LUA_METATABLE_ENUM(QAbstractSocket::SocketOption);
LUA_METATABLE_ENUM(QAbstractSocket::SocketState);
LUA_METATABLE_ENUM(QAbstractSocket::SocketType);

extern "C" int luaopen_Qt5Network_QAbstractSocket(lua_State* const);

#endif // LUACXX_QABSTRACTSOCKET_INCLUDED

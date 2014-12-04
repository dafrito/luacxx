#ifndef luacxx_QUdpSocket_INCLUDED
#define luacxx_QUdpSocket_INCLUDED

#include "Qt5Network.hpp"

#include <QUdpSocket>

#include "QAbstractSocket.hpp"

LUA_METATABLE_INHERIT(QUdpSocket, QAbstractSocket);

extern "C" int luaopen_Qt5Network_QUdpSocket(lua_State* const);

#endif // luacxx_QUdpSocket_INCLUDED

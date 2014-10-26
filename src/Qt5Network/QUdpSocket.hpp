#ifndef luacxx_QUdpSocket_INCLUDED
#define luacxx_QUdpSocket_INCLUDED

#include "Qt5Network.hpp"

#include <QUdpSocket>

LUA_METATABLE_BUILT(QUdpSocket);

extern "C" int luaopen_Qt5Network_QUdpSocket(lua_State* const);

#endif // luacxx_QUdpSocket_INCLUDED

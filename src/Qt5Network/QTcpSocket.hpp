#ifndef luacxx_QTcpSocket_INCLUDED
#define luacxx_QTcpSocket_INCLUDED

#include "Qt5Network.hpp"

#include <QTcpSocket>

LUA_METATABLE_BUILT(QTcpSocket);

extern "C" int luaopen_luacxx_QTcpSocket(lua_State* const);

#endif // luacxx_QTcpSocket_INCLUDED

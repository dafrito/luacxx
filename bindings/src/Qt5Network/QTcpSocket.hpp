#ifndef luacxx_QTcpSocket_INCLUDED
#define luacxx_QTcpSocket_INCLUDED

#include "../stack.hpp"

#include <QTcpSocket>

#include "QAbstractSocket.hpp"

// http://qt-project.org/doc/qt-5/qtcpsocket.html

LUA_METATABLE_INHERIT(QTcpSocket, QAbstractSocket)

extern "C" int luaopen_Qt5Network_QTcpSocket(lua_State* const);

#endif // luacxx_QTcpSocket_INCLUDED

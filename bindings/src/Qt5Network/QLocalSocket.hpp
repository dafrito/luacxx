#ifndef LUA_CXX_QLOCALSOCKET_INCLUDED
#define LUA_CXX_QLOCALSOCKET_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QLocalSocket>

#include "../Qt5Core/QIODevice.hpp"

// http://qt-project.org/doc/qt-5/qlocalsocket.html

LUA_METATABLE_INHERIT(QLocalSocket, QIODevice);
LUA_METATABLE_ENUM(QLocalSocket::LocalSocketError);
LUA_METATABLE_ENUM(QLocalSocket::LocalSocketState);

extern "C" int luaopen_Qt5Network_QLocalSocket(lua_State* const);

#endif // LUA_CXX_QLOCALSOCKET_INCLUDED

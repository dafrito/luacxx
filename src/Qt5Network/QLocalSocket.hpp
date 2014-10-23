#ifndef LUA_CXX_QLOCALSOCKET_INCLUDED
#define LUA_CXX_QLOCALSOCKET_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QLocalSocket>

LUA_METATABLE_BUILT(QLocalSocket);
LUA_METATABLE_ENUM(QLocalSocket::LocalSocketError);
LUA_METATABLE_ENUM(QLocalSocket::LocalSocketState);

extern "C" int luaopen_luacxx_QLocalSocket(lua_State* const);

#endif // LUA_CXX_QLOCALSOCKET_INCLUDED

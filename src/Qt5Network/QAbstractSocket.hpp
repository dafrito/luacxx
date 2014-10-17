#ifndef LUACXX_QABSTRACTSOCKET_INCLUDED
#define LUACXX_QABSTRACTSOCKET_INCLUDED

#include "../stack.hpp"

class QAbstractSocket;

LUA_METATABLE_BUILT(QAbstractSocket);

extern "C" int luaopen_Qt5Network_QAbstractSocket(lua_State* const);

#endif // LUACXX_QABSTRACTSOCKET_INCLUDED

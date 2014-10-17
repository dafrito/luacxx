#ifndef LUA_CXX_QLOCALSOCKET_INCLUDED
#define LUA_CXX_QLOCALSOCKET_INCLUDED

#include "../stack.hpp"

class QLocalSocket;

LUA_METATABLE_BUILT(QLocalSocket);

extern "C" int luaopen_luacxx_QLocalSocket(lua_State* const);

#endif // LUA_CXX_QLOCALSOCKET_INCLUDED

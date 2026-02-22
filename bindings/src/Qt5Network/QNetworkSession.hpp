#ifndef luacxx_QNetworkSession_INCLUDED
#define luacxx_QNetworkSession_INCLUDED

#include "../stack.hpp"

#include <QNetworkSession>

LUA_METATABLE_BUILT(QNetworkSession)

extern "C" int luaopen_luacxx_QNetworkSession(lua_State* const);

#endif // luacxx_QNetworkSession_INCLUDED

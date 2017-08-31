#ifndef luacxx_QNetworkProxyQuery_INCLUDED
#define luacxx_QNetworkProxyQuery_INCLUDED

#include "../stack.hpp"

#include <QNetworkProxyQuery>

LUA_METATABLE_BUILT(QNetworkProxyQuery)

extern "C" int luaopen_luacxx_QNetworkProxyQuery(lua_State* const);

#endif // luacxx_QNetworkProxyQuery_INCLUDED

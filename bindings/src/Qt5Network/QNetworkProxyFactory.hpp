#ifndef luacxx_QNetworkProxyFactory_INCLUDED
#define luacxx_QNetworkProxyFactory_INCLUDED

#include "../stack.hpp"

#include <QNetworkProxyFactory>

LUA_METATABLE_BUILT(QNetworkProxyFactory)

extern "C" int luaopen_luacxx_QNetworkProxyFactory(lua_State* const);

#endif // luacxx_QNetworkProxyFactory_INCLUDED

#ifndef luacxx_QNetworkProxy_INCLUDED
#define luacxx_QNetworkProxy_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QNetworkProxy>

LUA_METATABLE_BUILT(QNetworkProxy)
LUA_METATABLE_ENUM(QNetworkProxy::Capability)
LUA_METATABLE_ENUM(QNetworkProxy::ProxyType)

extern "C" int luaopen_Qt5Network_QNetworkProxy(lua_State* const);

#endif // luacxx_QNetworkProxy_INCLUDED

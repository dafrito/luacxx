#ifndef luacxx_QNetworkRequest_INCLUDED
#define luacxx_QNetworkRequest_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QNetworkRequest>

LUA_METATABLE_BUILT(QNetworkRequest)
LUA_METATABLE_ENUM(QNetworkRequest::Attribute)
LUA_METATABLE_ENUM(QNetworkRequest::CacheLoadControl)
LUA_METATABLE_ENUM(QNetworkRequest::KnownHeaders)
LUA_METATABLE_ENUM(QNetworkRequest::LoadControl)
LUA_METATABLE_ENUM(QNetworkRequest::Priority)

extern "C" int luaopen_Qt5Network_QNetworkRequest(lua_State* const);

#endif // luacxx_QNetworkRequest_INCLUDED

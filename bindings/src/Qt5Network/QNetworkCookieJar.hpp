#ifndef luacxx_QNetworkCookieJar_INCLUDED
#define luacxx_QNetworkCookieJar_INCLUDED

#include "../stack.hpp"

#include <QNetworkCookieJar>

LUA_METATABLE_BUILT(QNetworkCookieJar)

extern "C" int luaopen_luacxx_QNetworkCookieJar(lua_State* const);

#endif // luacxx_QNetworkCookieJar_INCLUDED

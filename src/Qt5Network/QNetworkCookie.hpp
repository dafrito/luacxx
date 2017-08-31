#ifndef luacxx_QNetworkCookie_INCLUDED
#define luacxx_QNetworkCookie_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QNetworkCookie>

// http://doc.qt.io/qt-5/qnetworkcookie.html

LUA_METATABLE_BUILT(QNetworkCookie)
LUA_METATABLE_ENUM(QNetworkCookie::RawForm)

extern "C" int luaopen_Qt5Network_QNetworkCookie(lua_State* const);

#endif // luacxx_QNetworkCookie_INCLUDED

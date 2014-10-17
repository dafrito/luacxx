#ifndef luacxx_QNetworkAddressEntry_INCLUDED
#define luacxx_QNetworkAddressEntry_INCLUDED

#include "Qt5Network.hpp"

#include <QNetworkAddressEntry>

LUA_METATABLE_BUILT(QNetworkAddressEntry);

extern "C" int luaopen_luacxx_QNetworkAddressEntry(lua_State* const);

#endif // luacxx_QNetworkAddressEntry_INCLUDED

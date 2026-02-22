#ifndef luacxx_QNetworkDiskCache_INCLUDED
#define luacxx_QNetworkDiskCache_INCLUDED

#include "../stack.hpp"

#include <QNetworkDiskCache>

LUA_METATABLE_BUILT(QNetworkDiskCache)

extern "C" int luaopen_luacxx_QNetworkDiskCache(lua_State* const);

#endif // luacxx_QNetworkDiskCache_INCLUDED

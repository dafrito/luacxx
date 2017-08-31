#ifndef luacxx_QNetworkCacheMetaData_INCLUDED
#define luacxx_QNetworkCacheMetaData_INCLUDED

#include "../stack.hpp"

#include <QNetworkCacheMetaData>

LUA_METATABLE_BUILT(QNetworkCacheMetaData)

extern "C" int luaopen_luacxx_QNetworkCacheMetaData(lua_State* const);

#endif // luacxx_QNetworkCacheMetaData_INCLUDED

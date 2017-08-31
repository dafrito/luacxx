#ifndef luacxx_QNetworkConfiguration_INCLUDED
#define luacxx_QNetworkConfiguration_INCLUDED

#include "../stack.hpp"

#include <QNetworkConfiguration>

LUA_METATABLE_BUILT(QNetworkConfiguration)

extern "C" int luaopen_luacxx_QNetworkConfiguration(lua_State* const);

#endif // luacxx_QNetworkConfiguration_INCLUDED

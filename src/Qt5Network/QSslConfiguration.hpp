#ifndef luacxx_QSslConfiguration_INCLUDED
#define luacxx_QSslConfiguration_INCLUDED

#include "Qt5Network.hpp"

#include <QSslConfiguration>

LUA_METATABLE_BUILT(QSslConfiguration);

extern "C" int luaopen_luacxx_QSslConfiguration(lua_State* const);

#endif // luacxx_QSslConfiguration_INCLUDED

#ifndef luacxx_QSslKey_INCLUDED
#define luacxx_QSslKey_INCLUDED

#include "Qt5Network.hpp"

#include <QSslKey>

LUA_METATABLE_BUILT(QSslKey);

extern "C" int luaopen_Qt5Network_QSslKey(lua_State* const);

#endif // luacxx_QSslKey_INCLUDED

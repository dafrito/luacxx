#ifndef luacxx_QSslError_INCLUDED
#define luacxx_QSslError_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QSslError>

LUA_METATABLE_BUILT(QSslError);
LUA_METATABLE_ENUM(QSslError::SslError);

extern "C" int luaopen_Qt5Network_QSslError(lua_State* const);

#endif // luacxx_QSslError_INCLUDED

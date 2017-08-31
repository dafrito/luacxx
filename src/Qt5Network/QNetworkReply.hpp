#ifndef luacxx_QNetworkReply_INCLUDED
#define luacxx_QNetworkReply_INCLUDED

#include "../stack.hpp"

#include <QNetworkReply>

LUA_METATABLE_BUILT(QNetworkReply)

extern "C" int luaopen_luacxx_QNetworkReply(lua_State* const);

#endif // luacxx_QNetworkReply_INCLUDED

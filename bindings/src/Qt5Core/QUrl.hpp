#ifndef LUACXX_QURL_INCLUDED
#define LUACXX_QURL_INCLUDED

#include "Qt5Core.hpp"
#include <QUrl>

LUA_METATABLE_BUILT(QUrl)

extern "C" int luaopen_Qt5Core_QUrl(lua_State* const);

#endif // LUACXX_QURL_INCLUDED

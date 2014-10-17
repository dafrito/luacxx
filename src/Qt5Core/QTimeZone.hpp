#ifndef luacxx_QTimeZone_INCLUDED
#define luacxx_QTimeZone_INCLUDED

#include "Qt5Core.hpp"

#include <QTimeZone>

LUA_METATABLE_BUILT(QTimeZone)

extern "C" int luaopen_luacxx_QTimeZone(lua_State* const);

#endif // luacxx_QTimeZone_INCLUDED

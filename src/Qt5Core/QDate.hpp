#ifndef luacxx_QDate_INCLUDED
#define luacxx_QDate_INCLUDED

#include "Qt5Core.hpp"

#include <QDate>

LUA_METATABLE_BUILT(QDate)

extern "C" int luaopen_luacxx_QDate(lua_State* const);

#endif // luacxx_QDate_INCLUDED

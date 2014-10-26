#ifndef luacxx_QDate_INCLUDED
#define luacxx_QDate_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include <QDate>

LUA_METATABLE_BUILT(QDate)
LUA_METATABLE_ENUM(QDate::MonthNameType);

extern "C" int luaopen_Qt5Core_QDate(lua_State* const);

#endif // luacxx_QDate_INCLUDED

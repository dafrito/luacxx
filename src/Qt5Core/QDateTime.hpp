#ifndef luacxx_QDateTime_INCLUDED
#define luacxx_QDateTime_INCLUDED

#include "Qt5Core.hpp"

#include <QDateTime>

LUA_METATABLE_BUILT(QDateTime)

extern "C" int luaopen_Qt5Core_QDateTime(lua_State* const);

#endif // luacxx_QDateTime_INCLUDED

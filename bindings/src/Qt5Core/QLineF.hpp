#ifndef luacxx_QLineF_INCLUDED
#define luacxx_QLineF_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include <QLineF>

LUA_METATABLE_BUILT(QLineF);
LUA_METATABLE_ENUM(QLineF::IntersectType);

extern "C" int luaopen_Qt5Core_QLineF(lua_State* const);

#endif // luacxx_QLineF_INCLUDED

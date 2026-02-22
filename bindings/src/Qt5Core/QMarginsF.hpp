#ifndef luacxx_QMarginsF_INCLUDED
#define luacxx_QMarginsF_INCLUDED

#include "../stack.hpp"

#include <QMarginsF>

LUA_METATABLE_BUILT(QMarginsF)

extern "C" int luaopen_Qt5Core_QMarginsF(lua_State* const);

#endif // luacxx_QMarginsF_INCLUDED

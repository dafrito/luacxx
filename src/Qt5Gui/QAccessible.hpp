#ifndef luacxx_QAccessible_INCLUDED
#define luacxx_QAccessible_INCLUDED

#include "../stack.hpp"

#include <QAccessible>

LUA_METATABLE_BUILT(QAccessible)

extern "C" int luaopen_luacxx_QAccessible(lua_State* const);

#endif // luacxx_QAccessible_INCLUDED

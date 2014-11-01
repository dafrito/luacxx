#ifndef luacxx_QMetaEnum_INCLUDED
#define luacxx_QMetaEnum_INCLUDED

#include "../stack.hpp"

#include <QMetaEnum>

LUA_METATABLE_BUILT(QMetaEnum)

extern "C" int luaopen_luacxx_QMetaEnum(lua_State* const);

#endif // luacxx_QMetaEnum_INCLUDED

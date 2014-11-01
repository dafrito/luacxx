#ifndef luacxx_QMetaProperty_INCLUDED
#define luacxx_QMetaProperty_INCLUDED

#include "../stack.hpp"

#include <QMetaProperty>

LUA_METATABLE_BUILT(QMetaProperty)

extern "C" int luaopen_luacxx_QMetaProperty(lua_State* const);

#endif // luacxx_QMetaProperty_INCLUDED

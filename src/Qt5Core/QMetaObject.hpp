#ifndef luacxx_QMetaObject_INCLUDED
#define luacxx_QMetaObject_INCLUDED

#include "../stack.hpp"

#include <QMetaObject>

LUA_METATABLE_BUILT(QMetaObject)
LUA_METATABLE_NAMED(QMetaObject::Connection)

extern "C" int luaopen_luacxx_QMetaObject(lua_State* const);

#endif // luacxx_QMetaObject_INCLUDED

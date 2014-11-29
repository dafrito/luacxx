#ifndef luacxx_QMetaMethod_INCLUDED
#define luacxx_QMetaMethod_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QMetaMethod>
#include "QString.hpp"

LUA_METATABLE_BUILT(QMetaMethod)
LUA_METATABLE_ENUM(QMetaMethod::MethodType)
LUA_METATABLE_ENUM(QMetaMethod::Access)

namespace lua {

QString QMetaMethod_signature(const QMetaMethod& method);

}

extern "C" int luaopen_Qt5Core_QMetaMethod(lua_State* const);

#endif // luacxx_QMetaMethod_INCLUDED

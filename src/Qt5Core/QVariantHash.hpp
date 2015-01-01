#ifndef luacxx_QVariantHash_INCLUDED
#define luacxx_QVariantHash_INCLUDED

#include "../stack.hpp"

#include <QVariantHash>

LUA_METATABLE_BUILT(QVariantHash)

extern "C" int luaopen_Qt5Core_QVariantHash(lua_State* const);

#endif // luacxx_QVariantHash_INCLUDED

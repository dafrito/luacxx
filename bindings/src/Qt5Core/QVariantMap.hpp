#ifndef luacxx_QVariantMap_INCLUDED
#define luacxx_QVariantMap_INCLUDED

#include "../stack.hpp"

#include <QVariantMap>

LUA_METATABLE_BUILT(QVariantMap)

extern "C" int luaopen_Qt5Core_QVariantMap(lua_State* const);

#endif // luacxx_QVariantMap_INCLUDED

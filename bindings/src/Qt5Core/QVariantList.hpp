#ifndef luacxx_QVariantList_INCLUDED
#define luacxx_QVariantList_INCLUDED

#include "../stack.hpp"

#include <QVariantList>

LUA_METATABLE_BUILT(QVariantList)

extern "C" int luaopen_Qt5Core_QVariantList(lua_State* const);

#endif // luacxx_QVariantList_INCLUDED

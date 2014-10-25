#ifndef luacxx_QSpacerItem_INCLUDED
#define luacxx_QSpacerItem_INCLUDED

#include "../stack.hpp"

#include <QSpacerItem>

LUA_METATABLE_BUILT(QSpacerItem)

extern "C" int luaopen_luacxx_QSpacerItem(lua_State* const);

#endif // luacxx_QSpacerItem_INCLUDED

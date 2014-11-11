#ifndef luacxx_QStyleOptionGraphicsItem_INCLUDED
#define luacxx_QStyleOptionGraphicsItem_INCLUDED

#include "../stack.hpp"

#include <QStyleOptionGraphicsItem>

#include "QStyleOption.hpp"

LUA_METATABLE_INHERIT(QStyleOptionGraphicsItem, QStyleOption)

extern "C" int luaopen_luacxx_QStyleOptionGraphicsItem(lua_State* const);

#endif // luacxx_QStyleOptionGraphicsItem_INCLUDED

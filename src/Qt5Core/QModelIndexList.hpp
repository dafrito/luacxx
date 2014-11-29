#ifndef luacxx_QModelIndexList_INCLUDED
#define luacxx_QModelIndexList_INCLUDED

#include "../stack.hpp"

#include <QModelIndexList>

LUA_METATABLE_BUILT(QModelIndexList)

extern "C" int luaopen_Qt5Core_QModelIndexList(lua_State* const);

#endif // luacxx_QModelIndexList_INCLUDED

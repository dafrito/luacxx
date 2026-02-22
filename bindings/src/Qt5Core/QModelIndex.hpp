#ifndef luacxx_QModelIndex_INCLUDED
#define luacxx_QModelIndex_INCLUDED

#include "Qt5Core.hpp"

class QModelIndex;

LUA_METATABLE_BUILT(QModelIndex)

extern "C" int luaopen_Qt5Core_QModelIndex(lua_State* const);

#endif // luacxx_QModelIndex_INCLUDED

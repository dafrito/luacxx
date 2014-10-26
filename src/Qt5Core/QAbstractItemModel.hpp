#ifndef luacxx_QAbstractItemModel_INCLUDED
#define luacxx_QAbstractItemModel_INCLUDED

#include "Qt5Core.hpp"

class QAbstractItemModel;

LUA_METATABLE_BUILT(QAbstractItemModel)

extern "C" int luaopen_Qt5Core_QAbstractItemModel(lua_State* const);

#endif // luacxx_QAbstractItemModel_INCLUDED

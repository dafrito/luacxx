#ifndef luacxx_QPersistentModelIndex_INCLUDED
#define luacxx_QPersistentModelIndex_INCLUDED

#include "../stack.hpp"

#include <QPersistentModelIndex>

// http://qt-project.org/doc/qt-5/qpersistentmodelindex.html

LUA_METATABLE_BUILT(QPersistentModelIndex)

extern "C" int luaopen_Qt5Core_QPersistentModelIndex(lua_State* const);

#endif // luacxx_QPersistentModelIndex_INCLUDED

#ifndef luacxx_QObjectList_INCLUDED
#define luacxx_QObjectList_INCLUDED

#include "../stack.hpp"

#include <QObjectList>

LUA_METATABLE_BUILT(QObjectList)

extern "C" int luaopen_Qt5Core_QObjectList(lua_State* const);

#endif // luacxx_QObjectList_INCLUDED

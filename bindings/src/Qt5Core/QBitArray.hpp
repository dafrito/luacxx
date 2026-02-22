#ifndef luacxx_QBitArray_INCLUDED
#define luacxx_QBitArray_INCLUDED

#include "../stack.hpp"

#include <QBitArray>

LUA_METATABLE_BUILT(QBitArray)

extern "C" int luaopen_Qt5Core_QBitArray(lua_State* const);

#endif // luacxx_QBitArray_INCLUDED

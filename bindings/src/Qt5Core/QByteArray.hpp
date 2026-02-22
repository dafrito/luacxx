#ifndef luacxx_QByteArray_INCLUDED
#define luacxx_QByteArray_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

class QByteArray;

LUA_METATABLE_BUILT(QByteArray);
LUA_METATABLE_ENUM(QByteArray::Base64Option)

extern "C" int luaopen_Qt5Core_QByteArray(lua_State* const);

#endif // luacxx_QByteArray_INCLUDED

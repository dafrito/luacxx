#ifndef luacxx_QPageSize_INCLUDED
#define luacxx_QPageSize_INCLUDED

#include "../stack.hpp"

#include <QPageSize>

LUA_METATABLE_BUILT(QPageSize)

extern "C" int luaopen_luacxx_QPageSize(lua_State* const);

#endif // luacxx_QPageSize_INCLUDED

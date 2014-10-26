#ifndef luacxx_QPdfWriter_INCLUDED
#define luacxx_QPdfWriter_INCLUDED

#include "../stack.hpp"

#include <QPdfWriter>

LUA_METATABLE_BUILT(QPdfWriter)

extern "C" int luaopen_luacxx_QPdfWriter(lua_State* const);

#endif // luacxx_QPdfWriter_INCLUDED

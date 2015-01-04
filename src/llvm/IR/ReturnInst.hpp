#ifndef luacxx_ReturnInst_INCLUDED
#define luacxx_ReturnInst_INCLUDED

#include "../stack.hpp"

#include <ReturnInst>

LUA_METATABLE_BUILT(ReturnInst)

extern "C" int luaopen_luacxx_ReturnInst(lua_State* const);

#endif // luacxx_ReturnInst_INCLUDED

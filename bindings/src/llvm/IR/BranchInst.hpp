#ifndef luacxx_BranchInst_INCLUDED
#define luacxx_BranchInst_INCLUDED

#include "../stack.hpp"

#include <BranchInst>

LUA_METATABLE_BUILT(BranchInst)

extern "C" int luaopen_luacxx_BranchInst(lua_State* const);

#endif // luacxx_BranchInst_INCLUDED

#ifndef luacxx_BasicBlock_INCLUDED
#define luacxx_BasicBlock_INCLUDED

#include "../../stack.hpp"

#include <BasicBlock>

LUA_METATABLE_BUILT(BasicBlock)

extern "C" int luaopen_luacxx_BasicBlock(lua_State* const);

#endif // luacxx_BasicBlock_INCLUDED

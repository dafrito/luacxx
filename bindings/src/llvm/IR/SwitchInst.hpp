#ifndef luacxx_SwitchInst_INCLUDED
#define luacxx_SwitchInst_INCLUDED

#include "../stack.hpp"

#include <SwitchInst>

LUA_METATABLE_BUILT(SwitchInst)

extern "C" int luaopen_luacxx_SwitchInst(lua_State* const);

#endif // luacxx_SwitchInst_INCLUDED

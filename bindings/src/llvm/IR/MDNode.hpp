#ifndef luacxx_MDNode_INCLUDED
#define luacxx_MDNode_INCLUDED

#include "../stack.hpp"

#include <MDNode>

LUA_METATABLE_BUILT(MDNode)

extern "C" int luaopen_luacxx_MDNode(lua_State* const);

#endif // luacxx_MDNode_INCLUDED

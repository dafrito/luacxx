#ifndef luacxx_QPaintEngineState_INCLUDED
#define luacxx_QPaintEngineState_INCLUDED

#include "../stack.hpp"

#include <QPaintEngineState>

LUA_METATABLE_BUILT(QPaintEngineState)

extern "C" int luaopen_luacxx_QPaintEngineState(lua_State* const);

#endif // luacxx_QPaintEngineState_INCLUDED

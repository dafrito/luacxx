#ifndef luacxx_QPolygonF_INCLUDED
#define luacxx_QPolygonF_INCLUDED

#include "../stack.hpp"

class QPolygonF;

LUA_METATABLE_BUILT(QPolygonF);

extern "C" int luaopen_luacxx_QPolygonF(lua_State* const);

#endif // luacxx_QPolygonF_INCLUDED

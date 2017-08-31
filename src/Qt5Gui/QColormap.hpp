#ifndef luacxx_QColormap_INCLUDED
#define luacxx_QColormap_INCLUDED

#include "../stack.hpp"

#include <QColormap>

LUA_METATABLE_BUILT(QColormap)

extern "C" int luaopen_luacxx_QColormap(lua_State* const);

#endif // luacxx_QColormap_INCLUDED

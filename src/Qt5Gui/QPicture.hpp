#ifndef luacxx_QPicture_INCLUDED
#define luacxx_QPicture_INCLUDED

#include "../stack.hpp"

class QPicture;

LUA_METATABLE_BUILT(QPicture);

extern "C" int luaopen_Qt5Gui_QPicture(lua_State* const);

#endif // luacxx_QPicture_INCLUDED

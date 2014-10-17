#ifndef luacxx_QActionGroup_INCLUDED
#define luacxx_QActionGroup_INCLUDED

#include "Qt5Widgets.hpp"

class QActionGroup;

LUA_METATABLE_BUILT(QActionGroup);

extern "C" int luaopen_luacxx_QActionGroup(lua_State* const);

#endif // luacxx_QActionGroup_INCLUDED

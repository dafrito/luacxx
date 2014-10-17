#ifndef luacxx_QMenu_INCLUDED
#define luacxx_QMenu_INCLUDED

#include "Qt5Widgets.hpp"

class QMenu;

LUA_METATABLE_BUILT(QMenu);

extern "C" int luaopen_luacxx_QMenu(lua_State* const);

#endif // luacxx_QMenu_INCLUDED

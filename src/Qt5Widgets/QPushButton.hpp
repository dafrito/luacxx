#ifndef luacxx_QPushButton_INCLUDED
#define luacxx_QPushButton_INCLUDED

#include "Qt5Widgets.hpp"

#include <QPushButton>

LUA_METATABLE_BUILT(QPushButton)

extern "C" int luaopen_Qt5Widgets_QPushButton(lua_State* const);

#endif // luacxx_QPushButton_INCLUDED

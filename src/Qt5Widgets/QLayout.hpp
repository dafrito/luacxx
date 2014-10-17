#ifndef luacxx_QLayout_INCLUDED
#define luacxx_QLayout_INCLUDED

#include "Qt5Widgets.hpp"

class QLayout;

LUA_METATABLE_BUILT(QLayout);

extern "C" int luaopen_Qt5Widgets_QLayout(lua_State* const);

#endif // luacxx_QLayout_INCLUDED

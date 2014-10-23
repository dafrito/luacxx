#ifndef luacxx_QLayout_INCLUDED
#define luacxx_QLayout_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QLayout>

LUA_METATABLE_BUILT(QLayout);
LUA_METATABLE_ENUM(QLayout::SizeConstraint);

extern "C" int luaopen_Qt5Widgets_QLayout(lua_State* const);

#endif // luacxx_QLayout_INCLUDED

#ifndef luacxx_QStyleOption_INCLUDED
#define luacxx_QStyleOption_INCLUDED

#include "Qt5Widgets.hpp"

#include <QStyleOption>

LUA_METATABLE_BUILT(QStyleOption)

extern "C" int luaopen_Qt5Widgets_QStyleOption(lua_State* const);

#endif // luacxx_QStyleOption_INCLUDED

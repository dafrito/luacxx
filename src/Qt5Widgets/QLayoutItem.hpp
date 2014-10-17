#ifndef luacxx_QLayoutItem_INCLUDED
#define luacxx_QLayoutItem_INCLUDED

#include "Qt5Widgets.hpp"

class QLayoutItem;

LUA_METATABLE_BUILT(QLayoutItem);

extern "C" int luaopen_Qt5Widgets_QLayoutItem(lua_State* const);

#endif // luacxx_QLayoutItem_INCLUDED

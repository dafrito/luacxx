#ifndef luacxx_QGraphicsItemGroup_INCLUDED
#define luacxx_QGraphicsItemGroup_INCLUDED

#include "Qt5Widgets.hpp"

class QGraphicsItemGroup;

LUA_METATABLE_BUILT(QGraphicsItemGroup);

extern "C" int luaopen_Qt5Widgets_QGraphicsItemGroup(lua_State* const);

#endif // luacxx_QGraphicsItemGroup_INCLUDED

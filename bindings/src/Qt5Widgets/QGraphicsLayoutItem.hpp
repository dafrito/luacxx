#ifndef luacxx_QGraphicsLayoutItem_INCLUDED
#define luacxx_QGraphicsLayoutItem_INCLUDED

#include "Qt5Widgets.hpp"

#include <QGraphicsLayoutItem>

LUA_METATABLE_BUILT(QGraphicsLayoutItem);

extern "C" int luaopen_Qt5Widgets_QGraphicsLayoutItem(lua_State* const);

#endif // luacxx_QGraphicsLayoutItem_INCLUDED

#ifndef luacxx_QGraphicsTransform_INCLUDED
#define luacxx_QGraphicsTransform_INCLUDED

#include "Qt5Widgets.hpp"

class QGraphicsTransform;

LUA_METATABLE_BUILT(QGraphicsTransform);

extern "C" int luaopen_Qt5Widgets_QGraphicsTransform(lua_State* const);

#endif // luacxx_QGraphicsTransform_INCLUDED

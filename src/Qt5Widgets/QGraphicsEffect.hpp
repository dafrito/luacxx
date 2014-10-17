#ifndef luacxx_QGraphicsEffect_INCLUDED
#define luacxx_QGraphicsEffect_INCLUDED

#include "Qt5Widgets.hpp"

class QGraphicsEffect;

LUA_METATABLE_BUILT(QGraphicsEffect);

extern "C" int luaopen_Qt5Widgets_QGraphicsEffect(lua_State* const);

#endif // luacxx_QGraphicsEffect_INCLUDED

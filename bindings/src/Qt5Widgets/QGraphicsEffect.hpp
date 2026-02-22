#ifndef luacxx_QGraphicsEffect_INCLUDED
#define luacxx_QGraphicsEffect_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QGraphicsEffect>

LUA_METATABLE_BUILT(QGraphicsEffect);
LUA_METATABLE_ENUM(QGraphicsEffect::ChangeFlag);
LUA_METATABLE_ENUM(QGraphicsEffect::PixmapPadMode);

extern "C" int luaopen_Qt5Widgets_QGraphicsEffect(lua_State* const);

#endif // luacxx_QGraphicsEffect_INCLUDED

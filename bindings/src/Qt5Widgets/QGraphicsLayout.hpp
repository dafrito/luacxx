#ifndef luacxx_QGraphicsLayout_INCLUDED
#define luacxx_QGraphicsLayout_INCLUDED

#include "../stack.hpp"

#include <QGraphicsLayout>

LUA_METATABLE_BUILT(QGraphicsLayout)

extern "C" int luaopen_Qt5Widgets_QGraphicsLayout(lua_State* const);

#endif // luacxx_QGraphicsLayout_INCLUDED

#ifndef luacxx_QGraphicsProxyWidget_INCLUDED
#define luacxx_QGraphicsProxyWidget_INCLUDED

#include "Qt5Widgets.hpp"

class QGraphicsProxyWidget;

LUA_METATABLE_BUILT(QGraphicsProxyWidget);

extern "C" int luaopen_Qt5Widgets_QGraphicsProxyWidget(lua_State* const);

#endif // luacxx_QGraphicsProxyWidget_INCLUDED

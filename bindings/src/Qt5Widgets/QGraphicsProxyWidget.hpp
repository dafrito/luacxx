#ifndef luacxx_QGraphicsProxyWidget_INCLUDED
#define luacxx_QGraphicsProxyWidget_INCLUDED

#include "Qt5Widgets.hpp"

#include <QGraphicsProxyWidget>
#include "QGraphicsWidget.hpp"

LUA_METATABLE_INHERIT(QGraphicsProxyWidget, QGraphicsWidget);

extern "C" int luaopen_Qt5Widgets_QGraphicsProxyWidget(lua_State* const);

#endif // luacxx_QGraphicsProxyWidget_INCLUDED

#ifndef luacxx_QGraphicsLineItem_INCLUDED
#define luacxx_QGraphicsLineItem_INCLUDED

#include "../stack.hpp"

#include <QGraphicsLineItem>

#include "QGraphicsItem.hpp"

// http://qt-project.org/doc/qt-5/qgraphicslineitem.html

LUA_METATABLE_INHERIT(QGraphicsLineItem, QGraphicsItem)

extern "C" int luaopen_Qt5Widgets_QGraphicsLineItem(lua_State* const);

#endif // luacxx_QGraphicsLineItem_INCLUDED

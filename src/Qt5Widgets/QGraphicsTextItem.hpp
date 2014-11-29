#ifndef luacxx_QGraphicsTextItem_INCLUDED
#define luacxx_QGraphicsTextItem_INCLUDED

#include "../stack.hpp"

#include <QGraphicsTextItem>

#include "QGraphicsObject.hpp"

// https://qt-project.org/doc/qt-5/qgraphicstextitem.html

LUA_METATABLE_INHERIT(QGraphicsTextItem, QGraphicsObject)

extern "C" int luaopen_Qt5Widgets_QGraphicsTextItem(lua_State* const);

#endif // luacxx_QGraphicsTextItem_INCLUDED

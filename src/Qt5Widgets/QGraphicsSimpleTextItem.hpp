#ifndef luacxx_QGraphicsSimpleTextItem_INCLUDED
#define luacxx_QGraphicsSimpleTextItem_INCLUDED

#include "../stack.hpp"

#include <QGraphicsSimpleTextItem>

#include "QAbstractGraphicsShapeItem.hpp"

// https://qt-project.org/doc/qt-5/qgraphicssimpletextitem.html

LUA_METATABLE_INHERIT(QGraphicsSimpleTextItem, QAbstractGraphicsShapeItem)

extern "C" int luaopen_Qt5Widgets_QGraphicsSimpleTextItem(lua_State* const);

#endif // luacxx_QGraphicsSimpleTextItem_INCLUDED

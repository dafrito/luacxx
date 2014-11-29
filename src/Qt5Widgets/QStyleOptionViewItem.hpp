#ifndef luacxx_QStyleOptionViewItem_INCLUDED
#define luacxx_QStyleOptionViewItem_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QStyleOptionViewItem>

#include "QStyleOption.hpp"

// http://qt-project.org/doc/qt-5/qstyleoptionviewitem.html

LUA_METATABLE_INHERIT(QStyleOptionViewItem, QStyleOption)
LUA_METATABLE_ENUM(QStyleOptionViewItem::Position)
LUA_METATABLE_ENUM(QStyleOptionViewItem::StyleOptionType)
LUA_METATABLE_ENUM(QStyleOptionViewItem::StyleOptionVersion)
LUA_METATABLE_ENUM(QStyleOptionViewItem::ViewItemFeature)
LUA_METATABLE_ENUM(QStyleOptionViewItem::ViewItemPosition)

extern "C" int luaopen_Qt5Widgets_QStyleOptionViewItem(lua_State* const);

#endif // luacxx_QStyleOptionViewItem_INCLUDED

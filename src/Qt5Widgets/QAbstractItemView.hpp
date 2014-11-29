#ifndef luacxx_QAbstractItemView_INCLUDED
#define luacxx_QAbstractItemView_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QAbstractItemView>

#include "QAbstractScrollArea.hpp"

// https://qt-project.org/doc/qt-5/qabstractitemview.html

LUA_METATABLE_INHERIT(QAbstractItemView, QAbstractScrollArea);
LUA_METATABLE_ENUM(QAbstractItemView::DragDropMode)
LUA_METATABLE_ENUM(QAbstractItemView::EditTrigger)
LUA_METATABLE_ENUM(QAbstractItemView::ScrollHint)
LUA_METATABLE_ENUM(QAbstractItemView::ScrollMode)
LUA_METATABLE_ENUM(QAbstractItemView::SelectionBehavior)
LUA_METATABLE_ENUM(QAbstractItemView::SelectionMode)

extern "C" int luaopen_Qt5Widgets_QAbstractItemView(lua_State* const);

#endif // luacxx_QAbstractItemView_INCLUDED

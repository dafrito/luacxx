#ifndef luacxx_QAbstractItemDelegate_INCLUDED
#define luacxx_QAbstractItemDelegate_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QAbstractItemDelegate>

#include "../Qt5Core/QObject.hpp"

// http://qt-project.org/doc/qt-5/qabstractitemdelegate.html

LUA_METATABLE_INHERIT(QAbstractItemDelegate, QObject)
LUA_METATABLE_ENUM(QAbstractItemDelegate::EndEditHint)

extern "C" int luaopen_Qt5Widgets_QAbstractItemDelegate(lua_State* const);

#endif // luacxx_QAbstractItemDelegate_INCLUDED

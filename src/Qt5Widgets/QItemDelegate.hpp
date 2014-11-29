#ifndef luacxx_QItemDelegate_INCLUDED
#define luacxx_QItemDelegate_INCLUDED

#include "../stack.hpp"

#include <QItemDelegate>

#include "QAbstractItemDelegate.hpp"

// http://qt-project.org/doc/qt-5/qitemdelegate.html

LUA_METATABLE_INHERIT(QItemDelegate, QAbstractItemDelegate)

extern "C" int luaopen_Qt5Widgets_QItemDelegate(lua_State* const);

#endif // luacxx_QItemDelegate_INCLUDED

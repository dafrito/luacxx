#ifndef luacxx_QSqlRelationalDelegate_INCLUDED
#define luacxx_QSqlRelationalDelegate_INCLUDED

#include "../stack.hpp"

#include <QSqlRelationalDelegate>

#include "../Qt5Widgets/QItemDelegate.hpp"

// http://qt-project.org/doc/qt-5/qsqlrelationaldelegate.html

#ifdef QT_WIDGETS_LIB
LUA_METATABLE_INHERIT(QSqlRelationalDelegate, QItemDelegate)
#endif

extern "C" int luaopen_Qt5Sql_QSqlRelationalDelegate(lua_State* const);

#endif // luacxx_QSqlRelationalDelegate_INCLUDED

#ifndef luacxx_QSqlQueryModel_INCLUDED
#define luacxx_QSqlQueryModel_INCLUDED

#include "../stack.hpp"

#include <QSqlQueryModel>

#include "../Qt5Core/QAbstractTableModel.hpp"

// http://qt-project.org/doc/qt-5/qsqlquerymodel.html

LUA_METATABLE_INHERIT(QSqlQueryModel, QAbstractTableModel)

extern "C" int luaopen_Qt5Sql_QSqlQueryModel(lua_State* const);

#endif // luacxx_QSqlQueryModel_INCLUDED

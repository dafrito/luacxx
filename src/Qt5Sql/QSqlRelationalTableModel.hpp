#ifndef luacxx_QSqlRelationalTableModel_INCLUDED
#define luacxx_QSqlRelationalTableModel_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QSqlRelationalTableModel>

#include "QSqlTableModel.hpp"

// http://qt-project.org/doc/qt-5/qsqlrelationaltablemodel.html

LUA_METATABLE_INHERIT(QSqlRelationalTableModel, QSqlTableModel)
LUA_METATABLE_ENUM(QSqlRelationalTableModel::JoinMode)

extern "C" int luaopen_Qt5Sql_QSqlRelationalTableModel(lua_State* const);

#endif // luacxx_QSqlRelationalTableModel_INCLUDED

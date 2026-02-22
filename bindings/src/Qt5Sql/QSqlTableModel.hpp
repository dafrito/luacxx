#ifndef luacxx_QSqlTableModel_INCLUDED
#define luacxx_QSqlTableModel_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QSqlTableModel>

#include "QSqlQueryModel.hpp"

// http://qt-project.org/doc/qt-5/qsqltablemodel.html

LUA_METATABLE_INHERIT(QSqlTableModel, QSqlQueryModel)
LUA_METATABLE_ENUM(QSqlTableModel::EditStrategy)

extern "C" int luaopen_Qt5Sql_QSqlTableModel(lua_State* const);

#endif // luacxx_QSqlTableModel_INCLUDED

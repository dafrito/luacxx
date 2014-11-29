#ifndef luacxx_QSql_INCLUDED
#define luacxx_QSql_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QSql>

LUA_METATABLE_ENUM(QSql::Location)
LUA_METATABLE_ENUM(QSql::NumericalPrecisionPolicy)
LUA_METATABLE_ENUM(QSql::ParamTypeFlag)
LUA_METATABLE_ENUM(QSql::TableType)

extern "C" int luaopen_Qt5Sql_QSql(lua_State* const);

#endif // luacxx_QSql_INCLUDED

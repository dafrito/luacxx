#ifndef luacxx_QSqlQuery_INCLUDED
#define luacxx_QSqlQuery_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QSqlQuery>

LUA_METATABLE_BUILT(QSqlQuery)
LUA_METATABLE_ENUM(QSqlQuery::BatchExecutionMode)

extern "C" int luaopen_Qt5Sql_QSqlQuery(lua_State* const);

#endif // luacxx_QSqlQuery_INCLUDED

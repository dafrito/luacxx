#ifndef luacxx_QSqlRelation_INCLUDED
#define luacxx_QSqlRelation_INCLUDED

#include "../stack.hpp"

#include <QSqlRelation>

LUA_METATABLE_BUILT(QSqlRelation)

extern "C" int luaopen_Qt5Sql_QSqlRelation(lua_State* const);

#endif // luacxx_QSqlRelation_INCLUDED

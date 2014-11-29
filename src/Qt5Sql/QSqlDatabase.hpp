#ifndef luacxx_QSqlDatabase_INCLUDED
#define luacxx_QSqlDatabase_INCLUDED

#include "../stack.hpp"

#include <QSqlDatabase>

LUA_METATABLE_BUILT(QSqlDatabase)

extern "C" int luaopen_Qt5Sql_QSqlDatabase(lua_State* const);

#endif // luacxx_QSqlDatabase_INCLUDED

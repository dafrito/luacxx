#ifndef luacxx_QSqlRecord_INCLUDED
#define luacxx_QSqlRecord_INCLUDED

#include "../stack.hpp"

#include <QSqlRecord>

#include "QSqlIndex.hpp"

LUA_METATABLE_BUILT(QSqlRecord);

extern "C" int luaopen_Qt5Sql_QSqlRecord(lua_State* const);

#endif // luacxx_QSqlRecord_INCLUDED

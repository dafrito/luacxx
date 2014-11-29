#ifndef luacxx_QSqlIndex_INCLUDED
#define luacxx_QSqlIndex_INCLUDED

#include "../stack.hpp"

#include <QSqlIndex>

#include "QSqlRecord.hpp"

// http://qt-project.org/doc/qt-5/qsqlindex.html

LUA_METATABLE_INHERIT(QSqlIndex, QSqlRecord)

extern "C" int luaopen_Qt5Sql_QSqlIndex(lua_State* const);

#endif // luacxx_QSqlIndex_INCLUDED

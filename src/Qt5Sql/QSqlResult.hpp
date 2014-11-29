#ifndef luacxx_QSqlResult_INCLUDED
#define luacxx_QSqlResult_INCLUDED

#include "../stack.hpp"

#include <QSqlResult>

// http://qt-project.org/doc/qt-5/qsqlresult.html

LUA_METATABLE_BUILT(QSqlResult)

extern "C" int luaopen_Qt5Sql_QSqlResult(lua_State* const);

#endif // luacxx_QSqlResult_INCLUDED

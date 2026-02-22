#ifndef luacxx_QSqlError_INCLUDED
#define luacxx_QSqlError_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QSqlError>

// http://qt-project.org/doc/qt-5/qsqlerror.html

LUA_METATABLE_BUILT(QSqlError)
LUA_METATABLE_ENUM(QSqlError::ErrorType)

extern "C" int luaopen_Qt5Sql_QSqlError(lua_State* const);

#endif // luacxx_QSqlError_INCLUDED

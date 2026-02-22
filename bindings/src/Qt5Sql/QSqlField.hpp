#ifndef luacxx_QSqlField_INCLUDED
#define luacxx_QSqlField_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QSqlField>

LUA_METATABLE_BUILT(QSqlField)
LUA_METATABLE_ENUM(QSqlField::RequiredStatus)

extern "C" int luaopen_Qt5Sql_QSqlField(lua_State* const);

#endif // luacxx_QSqlField_INCLUDED

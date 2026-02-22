#ifndef luacxx_QSqlDriver_INCLUDED
#define luacxx_QSqlDriver_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QSqlDriver>

#include "../Qt5Core/QObject.hpp"

LUA_METATABLE_INHERIT(QSqlDriver, QObject)
LUA_METATABLE_ENUM(QSqlDriver::DriverFeature)
LUA_METATABLE_ENUM(QSqlDriver::IdentifierType)
LUA_METATABLE_ENUM(QSqlDriver::NotificationSource)
LUA_METATABLE_ENUM(QSqlDriver::StatementType)

extern "C" int luaopen_Qt5Sql_QSqlDriver(lua_State* const);

#endif // luacxx_QSqlDriver_INCLUDED

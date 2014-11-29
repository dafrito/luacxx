#include "QSqlDatabase.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QStringList.hpp"

#include "QSql.hpp"
#include "QSqlQuery.hpp"
#include "QSqlDriver.hpp"
#include "QSqlIndex.hpp"
#include "QSqlRecord.hpp"
#include "QSqlError.hpp"
#include "QSqlDriverCreatorBase.hpp"

// http://qt-project.org/doc/qt-5/qsqldatabase.html

int QSqlDatabase_exec(lua_State* const state)
{
    auto self = lua::get<QSqlDatabase*>(state, 1);
    if (lua_gettop(state) == 1) {
        lua::push(state, self->exec());
    } else {
        lua::push(state, self->exec(lua::get<QString>(state, 2)));
    }
    return 1;
}

int QSqlDatabase_open(lua_State* const state)
{
    auto self = lua::get<QSqlDatabase*>(state, 1);
    if (lua_gettop(state) == 1) {
        // bool open()
        lua::push(state, self->open());
    } else {
        // bool open(const QString & user, const QString & password)
        lua::push(state, self->open(
            lua::get<QString>(state, 2),
            lua::get<QString>(state, 3)
        ));
    }
    return 1;
}

int QSqlDatabase_setConnectOptions(lua_State* const state)
{
    auto self = lua::get<QSqlDatabase*>(state, 1);
    if (lua_gettop(state) == 1) {
        // void setConnectOptions()
        self->setConnectOptions();
    } else {
        // void setConnectOptions(const QString & options = QString())
        self->setConnectOptions(lua::get<QString>(state, 2));
    }
    return 0;
}

int QSqlDatabase_tables(lua_State* const state)
{
    auto self = lua::get<QSqlDatabase*>(state, 1);
    if (lua_gettop(state) == 1) {
        // QStringList tables();
        lua::push(state, self->tables());
    } else {
        // QStringList tables(QSql::TableType type) const
        lua::push(state, self->tables(
            lua::get<QSql::TableType>(state, 2)
        ));
    }
    return 1;
}

namespace lua {

void QSqlDatabase_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["close"] = &QSqlDatabase::close;
    mt["commit"] = &QSqlDatabase::commit;
    mt["connectOptions"] = &QSqlDatabase::connectOptions;
    mt["connectionName"] = &QSqlDatabase::connectionName;
    mt["databaseName"] = &QSqlDatabase::databaseName;
    mt["driver"] = &QSqlDatabase::driver;
    mt["driverName"] = &QSqlDatabase::driverName;
    mt["exec"] = QSqlDatabase_exec;
    mt["hostName"] = &QSqlDatabase::hostName;
    mt["isOpen"] = &QSqlDatabase::isOpen;
    mt["isOpenError"] = &QSqlDatabase::isOpenError;
    mt["isValid"] = &QSqlDatabase::isValid;
    mt["lastError"] = &QSqlDatabase::lastError;
    mt["numericalPrecisionPolicy"] = &QSqlDatabase::numericalPrecisionPolicy;
    mt["open"] = QSqlDatabase_open;
    mt["password"] = &QSqlDatabase::password;
    mt["port"] = &QSqlDatabase::port;
    mt["primaryIndex"] = &QSqlDatabase::primaryIndex;
    mt["record"] = &QSqlDatabase::record;
    mt["rollback"] = &QSqlDatabase::rollback;
    mt["setConnectOptions"] = QSqlDatabase_setConnectOptions;
    mt["setDatabaseName"] = &QSqlDatabase::setDatabaseName;
    mt["setHostName"] = &QSqlDatabase::setHostName;
    mt["setNumericalPrecisionPolicy"] = &QSqlDatabase::setNumericalPrecisionPolicy;
    mt["setPassword"] = &QSqlDatabase::setPassword;
    mt["setPort"] = &QSqlDatabase::setPort;
    mt["setUserName"] = &QSqlDatabase::setUserName;
    mt["tables"] = QSqlDatabase_tables;
    mt["transaction"] = &QSqlDatabase::transaction;
    mt["userName"] = &QSqlDatabase::userName;
}

} // namespace lua

int QSqlDatabase_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QSqlDatabase>(state);
    } else {
        lua::make<QSqlDatabase>(state, lua::get<const QSqlDatabase&>(state, 1));
    }
    return 1;
}

int QSqlDatabase_addDatabase(lua_State* const state)
{
    if (lua::is_type<QSqlDriver>(state, 1)) {
        if (lua_gettop(state) == 1) {
            // QSqlDatabase addDatabase(QSqlDriver * driver)
            lua::push(state, QSqlDatabase::addDatabase(
                lua::get<QSqlDriver*>(state, 1)
            ));
        } else {
            // QSqlDatabase addDatabase(QSqlDriver * driver, const QString & connectionName = QLatin1String( defaultConnection ))
            lua::push(state, QSqlDatabase::addDatabase(
                lua::get<QSqlDriver*>(state, 1),
                lua::get<QString>(state, 2)
            ));
        }
    } else {
        if (lua_gettop(state) == 1) {
            // QSqlDatabase addDatabase(const QString & type)
            lua::push(state, QSqlDatabase::addDatabase(
                lua::get<QString>(state, 1)
            ));
        } else {
            // QSqlDatabase addDatabase(const QString & type, const QString & connectionName = QLatin1String( defaultConnection ))
            lua::push(state, QSqlDatabase::addDatabase(
                lua::get<QString>(state, 1),
                lua::get<QString>(state, 2)
            ));
        }

    }

    return 1;
}

int QSqlDatabase_contains(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // bool     contains()
        lua::push(state, QSqlDatabase::contains());
    } else {
        // bool     contains(const QString & connectionName = QLatin1String( defaultConnection ))
        lua::push(state, QSqlDatabase::contains(
            lua::get<QString>(state, 1)
        ));
    }

    return 1;
}

int QSqlDatabase_database(lua_State* const state)
{
    auto self = lua::get<QSqlDatabase*>(state, 1);

    switch (lua_gettop(state)) {
    case 0:
        // QSqlDatabase database()
        lua::push(state, QSqlDatabase::database());
        break;
    case 1:
        // QSqlDatabase database(const QString & connectionName)
        lua::push(state, QSqlDatabase::database(
            lua::get<QString>(state, 1)
        ));
        break;
    case 2:
    default:
        // QSqlDatabase database(const QString & connectionName, bool open)
        lua::push(state, QSqlDatabase::database(
            lua::get<QString>(state, 1),
            lua::get<bool>(state, 2)
        ));
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlDatabase(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlDatabase"] = lua::value::table;
    env["QSqlDatabase"]["new"] = QSqlDatabase_new;
    auto t = env["QSqlDatabase"];

    t["addDatabase"] = QSqlDatabase_addDatabase;
    t["cloneDatabase"] = QSqlDatabase::cloneDatabase;
    t["connectionNames"] = QSqlDatabase::connectionNames;
    t["contains"] = QSqlDatabase_contains;
    t["database"] = QSqlDatabase_database;
    t["drivers"] = QSqlDatabase::drivers;
    t["isDriverAvailable"] = QSqlDatabase::isDriverAvailable;
    t["registerSqlDriver"] = &QSqlDatabase::registerSqlDriver;
    t["removeDatabase"] = &QSqlDatabase::removeDatabase;

    return 0;
}

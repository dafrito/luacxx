#include "QSqlDriver.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QStringList.hpp"
#include "../Qt5Core/QVariant.hpp"

#include "QSqlField.hpp"
#include "QSqlError.hpp"
#include "QSqlIndex.hpp"
#include "QSqlRecord.hpp"
#include "QSql.hpp"

// http://qt-project.org/doc/qt-5/qsqldriver.html

int QSqlDriver_formatValue(lua_State* const state)
{
    auto self = lua::get<QSqlDriver*>(state, 1);
    if (lua_gettop(state) == 2) {
        lua::push(state, self->formatValue(
            lua::get<const QSqlField&>(state, 2)
        ));
    } else {
        lua::push(state, self->formatValue(
            lua::get<const QSqlField&>(state, 2),
            lua::get<bool>(state, 3)
        ));
    }
    return 1;
}

namespace lua {

void QSqlDriver_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["beginTransaction"] = &QSqlDriver::beginTransaction;
    mt["commitTransaction"] = &QSqlDriver::commitTransaction;
    mt["escapeIdentifier"] = &QSqlDriver::escapeIdentifier;
    mt["formatValue"] = QSqlDriver_formatValue;
    mt["handle"] = &QSqlDriver::handle;
    mt["isIdentifierEscaped"] = &QSqlDriver::isIdentifierEscaped;
    mt["isOpen"] = &QSqlDriver::isOpen;
    mt["isOpenError"] = &QSqlDriver::isOpenError;
    mt["lastError"] = &QSqlDriver::lastError;
    mt["numericalPrecisionPolicy"] = &QSqlDriver::numericalPrecisionPolicy;
    mt["primaryIndex"] = &QSqlDriver::primaryIndex;
    mt["record"] = &QSqlDriver::record;
    mt["rollbackTransaction"] = &QSqlDriver::rollbackTransaction;
    mt["setNumericalPrecisionPolicy"] = &QSqlDriver::setNumericalPrecisionPolicy;
    mt["sqlStatement"] = &QSqlDriver::sqlStatement;
    mt["stripDelimiters"] = &QSqlDriver::stripDelimiters;
    mt["subscribeToNotification"] = &QSqlDriver::subscribeToNotification;
    mt["subscribedToNotifications"] = &QSqlDriver::subscribedToNotifications;
    mt["tables"] = &QSqlDriver::tables;
    mt["unsubscribeFromNotification"] = &QSqlDriver::unsubscribeFromNotification;
}

} // namespace lua

int luaopen_Qt5Sql_QSqlDriver(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlDriver"] = lua::value::table;
    auto t = env["QSqlDriver"];

    // enum QSqlDriver::DriverFeature
    t["Transactions"] = QSqlDriver::Transactions;
    t["QuerySize"] = QSqlDriver::QuerySize;
    t["BLOB"] = QSqlDriver::BLOB;
    t["Unicode"] = QSqlDriver::Unicode;
    t["PreparedQueries"] = QSqlDriver::PreparedQueries;
    t["NamedPlaceholders"] = QSqlDriver::NamedPlaceholders;
    t["PositionalPlaceholders"] = QSqlDriver::PositionalPlaceholders;
    t["LastInsertId"] = QSqlDriver::LastInsertId;
    t["BatchOperations"] = QSqlDriver::BatchOperations;
    t["SimpleLocking"] = QSqlDriver::SimpleLocking;
    t["LowPrecisionNumbers"] = QSqlDriver::LowPrecisionNumbers;
    t["EventNotifications"] = QSqlDriver::EventNotifications;
    t["FinishQuery"] = QSqlDriver::FinishQuery;
    t["MultipleResultSets"] = QSqlDriver::MultipleResultSets;
    t["CancelQuery"] = QSqlDriver::CancelQuery;

    // enum QSqlDriver::IdentifierType
    t["FieldName"] = QSqlDriver::FieldName;
    t["TableName"] = QSqlDriver::TableName;

    // enum QSqlDriver::NotificationSource
    t["UnknownSource"] = QSqlDriver::UnknownSource;
    t["SelfSource"] = QSqlDriver::SelfSource;
    t["OtherSource"] = QSqlDriver::OtherSource;

    // enum QSqlDriver::StatementType
    t["WhereStatement"] = QSqlDriver::WhereStatement;
    t["SelectStatement"] = QSqlDriver::SelectStatement;
    t["UpdateStatement"] = QSqlDriver::UpdateStatement;
    t["InsertStatement"] = QSqlDriver::InsertStatement;
    t["DeleteStatement"] = QSqlDriver::DeleteStatement;

    return 0;
}

#include "QSqlQuery.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QMap.hpp"
#include "../Qt5Core/QFlags.hpp"

#include "QSqlDriver.hpp"
#include "QSqlError.hpp"
#include "QSqlRecord.hpp"
#include "QSqlResult.hpp"
#include "QSqlDatabase.hpp"
#include "QSql.hpp"

int QSqlQuery_addBindValue(lua_State* const state)
{
    auto self = lua::get<QSqlQuery*>(state, 1);
    if (lua_gettop(state) == 2) {
        // void addBindValue(const QVariant & val)
        self->addBindValue(
            lua::get<const QVariant&>(state, 2)
        );
    } else {
        // void addBindValue(const QVariant & val, QSql::ParamType paramType = QSql::In)
        self->addBindValue(
            lua::get<const QVariant&>(state, 2),
            lua::get<QSql::ParamType>(state, 3)
        );
    }
    return 0;
}

int QSqlQuery_bindValue(lua_State* const state)
{
    auto self = lua::get<QSqlQuery*>(state, 1);
    if (lua_type(state, 2) == LUA_TNUMBER) {
        // void bindValue(int pos, const QVariant & val, QSql::ParamType paramType = QSql::In)
        if (lua_gettop(state) == 3) {
            self->bindValue(
                lua::get<int>(state, 2),
                lua::get<QVariant>(state, 3)
            );
        } else {
            self->bindValue(
                lua::get<int>(state, 2),
                lua::get<QVariant>(state, 3),
                lua::get<QSql::ParamType>(state, 4)
            );
        }
    } else {
        if (lua_gettop(state) == 3) {
            // void bindValue(const QString & placeholder, const QVariant & val)
            self->bindValue(
                lua::get<QString>(state, 2),
                lua::get<QVariant>(state, 3)
            );
        } else {
            // void bindValue(const QString & placeholder, const QVariant & val, QSql::ParamType paramType)
            self->bindValue(
                lua::get<QString>(state, 2),
                lua::get<QVariant>(state, 3),
                lua::get<QSql::ParamType>(state, 4)
            );
        }
    }
    return 0;
}

int QSqlQuery_boundValue(lua_State* const state)
{
    auto self = lua::get<QSqlQuery*>(state, 1);
    if (lua_type(state, 2) == LUA_TNUMBER) {
        // QVariant boundValue(int pos) const
        lua::push(state, self->boundValue(lua::get<int>(state, 2)));
    } else {
        // QVariant boundValue(const QString & placeholder) const
        lua::push(state, self->boundValue(lua::get<QString>(state, 2)));
    }
    return 1;
}

int QSqlQuery_exec(lua_State* const state)
{
    auto self = lua::get<QSqlQuery*>(state, 1);
    if (lua_gettop(state) == 1) {
        // bool exec()
        lua::push(state, self->exec());
    } else {
        // bool exec(const QString & query)
        lua::push(state, self->exec(lua::get<QString>(state, 2)));
    }
    return 1;
}

int QSqlQuery_execBatch(lua_State* const state)
{
    auto self = lua::get<QSqlQuery*>(state, 1);
    if (lua_gettop(state) == 1) {
        // bool execBatch()
        lua::push(state, self->execBatch());
    } else {
        // bool execBatch(BatchExecutionMode mode = ValuesAsRows)
        lua::push(state, self->execBatch(lua::get<QSqlQuery::BatchExecutionMode>(state, 2)));
    }
    return 1;
}

int QSqlQuery_isNull(lua_State* const state)
{
    auto self = lua::get<QSqlQuery*>(state, 1);
    if (lua_type(state, 2) == LUA_TNUMBER) {
        // bool isNull(int field) const
        lua::push(state, self->isNull(lua::get<int>(state, 2)));
    } else {
        // bool isNull(const QString & name) const
        lua::push(state, self->isNull(lua::get<QString>(state, 2)));
    }
    return 1;
}

int QSqlQuery_seek(lua_State* const state)
{
    auto self = lua::get<QSqlQuery*>(state, 1);
    // bool seek(int index, bool relative = false)
    if (lua_gettop(state) == 2) {
        lua::push(state, self->seek(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->seek(
            lua::get<int>(state, 2),
            lua::get<bool>(state, 3)
        ));
    }
    return 1;
}

int QSqlQuery_value(lua_State* const state)
{
    auto self = lua::get<QSqlQuery*>(state, 1);
    if (lua_type(state, 2) == LUA_TNUMBER) {
        // QVariant value(int index) const
        lua::push(state, self->value(lua::get<int>(state, 2)));
    } else {
        // QVariant value(const QString & name) const
        lua::push(state, self->value(lua::get<QString>(state, 2)));
    }
    return 1;
}

namespace lua {

void QSqlQuery_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["addBindValue"] = QSqlQuery_addBindValue;
    mt["at"] = &QSqlQuery::at;
    mt["bindValue"] = QSqlQuery_bindValue;
    mt["boundValue"] = QSqlQuery_boundValue;
    mt["boundValues"] = &QSqlQuery::boundValues;
    mt["clear"] = &QSqlQuery::clear;
    mt["driver"] = &QSqlQuery::driver;
    mt["exec"] = QSqlQuery_exec;
    mt["execBatch"] = QSqlQuery_execBatch;
    mt["executedQuery"] = &QSqlQuery::executedQuery;
    mt["finish"] = &QSqlQuery::finish;
    mt["first"] = &QSqlQuery::first;
    mt["isActive"] = &QSqlQuery::isActive;
    mt["isForwardOnly"] = &QSqlQuery::isForwardOnly;
    mt["isNull"] = QSqlQuery_isNull;
    mt["isSelect"] = &QSqlQuery::isSelect;
    mt["isValid"] = &QSqlQuery::isValid;
    mt["last"] = &QSqlQuery::last;
    mt["lastError"] = &QSqlQuery::lastError;
    mt["lastInsertId"] = &QSqlQuery::lastInsertId;
    mt["lastQuery"] = &QSqlQuery::lastQuery;
    mt["next"] = &QSqlQuery::next;
    mt["nextResult"] = &QSqlQuery::nextResult;
    mt["numRowsAffected"] = &QSqlQuery::numRowsAffected;
    mt["numericalPrecisionPolicy"] = &QSqlQuery::numericalPrecisionPolicy;
    mt["prepare"] = &QSqlQuery::prepare;
    mt["previous"] = &QSqlQuery::previous;
    mt["record"] = &QSqlQuery::record;
    mt["result"] = &QSqlQuery::result;
    mt["seek"] = QSqlQuery_seek;
    mt["setForwardOnly"] = &QSqlQuery::setForwardOnly;
    mt["setNumericalPrecisionPolicy"] = &QSqlQuery::setNumericalPrecisionPolicy;
    mt["size"] = &QSqlQuery::size;
    mt["value"] = QSqlQuery_value;
}

} // namespace lua

int QSqlQuery_new(lua_State* const state)
{
    if (lua::is_type<QSqlDatabase>(state, 1)) {
        // QSqlQuery(QSqlDatabase db)
        lua::make<QSqlQuery>(state, lua::get<QSqlDatabase>(state, 1));
    } else if (lua::is_type<QSqlQuery>(state, 1)) {
        // QSqlQuery(const QSqlQuery & other)
        lua::make<QSqlQuery>(state, lua::get<const QSqlQuery&>(state, 1));
    } else if (lua::is_type<QSqlResult>(state, 1)) {
        // QSqlQuery(QSqlResult * result)
        lua::make<QSqlQuery>(state, lua::get<QSqlResult*>(state, 1));
    } else {
        switch (lua_gettop(state)) {
        case 0:
            // QSqlQuery()
            lua::make<QSqlQuery>(state);
            break;
        case 1:
            // QSqlQuery(const QString & query)
            lua::make<QSqlQuery>(state,
                lua::get<QString>(state, 1)
            );
            break;
        case 2:
        default:
            // QSqlQuery(const QString & query, QSqlDatabase db)
            lua::make<QSqlQuery>(state,
                lua::get<QString>(state, 1),
                lua::get<QSqlDatabase>(state, 2)
            );
            break;
        }
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlQuery(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlQuery"] = lua::value::table;
    env["QSqlQuery"]["new"] = QSqlQuery_new;
    auto t = env["QSqlQuery"];

    // enum QSqlQuery::BatchExecutionMode
    t["ValuesAsRows"] = QSqlQuery::ValuesAsRows;
    t["ValuesAsColumns"] = QSqlQuery::ValuesAsColumns;

    return 0;
}

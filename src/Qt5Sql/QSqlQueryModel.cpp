#include "QSqlQueryModel.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"

#include "QSqlDatabase.hpp"
#include "QSqlError.hpp"
#include "QSqlQuery.hpp"
#include "QSqlRecord.hpp"

int QSqlQueryModel_record(lua_State* const state)
{
    auto self = lua::get<QSqlQueryModel*>(state, 1);
    if (lua_gettop(state) == 1) {
        // QSqlRecord   record() const
        lua::push(state, self->record());
    } else {
        // QSqlRecord   record(int row) const
        lua::push(state, self->record(lua::get<int>(state, 2)));
    }
    return 1;
}

int QSqlQueryModel_setQuery(lua_State* const state)
{
    auto self = lua::get<QSqlQueryModel*>(state, 1);
    if (lua::is_type<QSqlQuery>(state, 2)) {
        // void setQuery(const QSqlQuery & query)
        self->setQuery(lua::get<const QSqlQuery&>(state, 2));
    } else {
        if (lua_gettop(state) == 2) {
            // void setQuery(const QString & query, const QSqlDatabase & db = QSqlDatabase())
            self->setQuery(
                lua::get<QString>(state, 2)
            );
        } else {
            // void setQuery(const QString & query, const QSqlDatabase & db = QSqlDatabase())
            self->setQuery(
                lua::get<QString>(state, 2),
                lua::get<const QSqlDatabase&>(state, 3)
            );
        }
    }
    return 0;
}

namespace lua {

void QSqlQueryModel_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractTableModel_metatable(state, pos);

    lua::index mt(state, pos);
    mt["clear"] = &QSqlQueryModel::clear;
    mt["lastError"] = &QSqlQueryModel::lastError;
    mt["query"] = &QSqlQueryModel::query;
    mt["record"] = QSqlQueryModel_record;
    mt["setQuery"] = QSqlQueryModel_setQuery;
}

} // namespace lua

int QSqlQueryModel_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::push(state, new QSqlQueryModel);
    } else {
        lua::push(state, new QSqlQueryModel(lua::get<QObject*>(state, 1)));
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlQueryModel(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlQueryModel"] = lua::value::table;
    env["QSqlQueryModel"]["new"] = QSqlQueryModel_new;
    auto t = env["QSqlQueryModel"];

    return 0;
}

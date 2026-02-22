#include "QSqlTableModel.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QSqlDatabase.hpp"
#include "QSqlRecord.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QModelIndex.hpp"
#include "QSqlIndex.hpp"

int QSqlTableModel_isDirty(lua_State* const state)
{
    auto self = lua::get<QSqlTableModel*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->isDirty());
    } else {
        lua::push(state, self->isDirty(
            lua::get<const QModelIndex&>(state, 2)
        ));
    }

    return 1;
}

int QSqlTableModel_record(lua_State* const state)
{
    auto self = lua::get<QSqlTableModel*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->record());
    } else {
        lua::push(state, self->record(
            lua::get<int>(state, 2)
        ));
    }

    return 1;
}

namespace lua {

void QSqlTableModel_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["database"] = &QSqlTableModel::database;
    mt["editStrategy"] = &QSqlTableModel::editStrategy;
    mt["fieldIndex"] = &QSqlTableModel::fieldIndex;
    mt["filter"] = &QSqlTableModel::filter;
    mt["insertRecord"] = &QSqlTableModel::insertRecord;
    mt["isDirty"] = QSqlTableModel_isDirty;
    mt["primaryKey"] = &QSqlTableModel::primaryKey;
    mt["record"] = QSqlTableModel_record;
    mt["revertRow"] = &QSqlTableModel::revertRow;
    mt["setEditStrategy"] = &QSqlTableModel::setEditStrategy;
    mt["setFilter"] = &QSqlTableModel::setFilter;
    mt["setRecord"] = &QSqlTableModel::setRecord;
    mt["setSort"] = &QSqlTableModel::setSort;
    mt["setTable"] = &QSqlTableModel::setTable;
    mt["tableName"] = &QSqlTableModel::tableName;
}

} // namespace lua

int QSqlTableModel_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        lua::push(state, new QSqlTableModel);
        break;
    case 1:
        lua::push(state, new QSqlTableModel(
            lua::get<QObject*>(state, 1)
        ));
        break;
    case 2:
    default:
        lua::push(state, new QSqlTableModel(
            lua::get<QObject*>(state, 1),
            lua::get<QSqlDatabase>(state, 2)
        ));
        break;
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlTableModel(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlTableModel"] = lua::value::table;
    env["QSqlTableModel"]["new"] = QSqlTableModel_new;
    auto t = env["QSqlTableModel"];

    // enum QSqlTableModel::EditStrategy
    t["OnFieldChange"] = QSqlTableModel::OnFieldChange;
    t["OnRowChange"] = QSqlTableModel::OnRowChange;
    t["OnManualSubmit"] = QSqlTableModel::OnManualSubmit;

    return 0;
}

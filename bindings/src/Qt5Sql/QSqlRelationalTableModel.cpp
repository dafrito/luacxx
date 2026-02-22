#include "QSqlRelationalTableModel.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QSqlRelation.hpp"
#include "QSqlTableModel.hpp"
#include "QSqlDatabase.hpp"

namespace lua {

void QSqlRelationalTableModel_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["relation"] = &QSqlRelationalTableModel::relation;
    mt["relationModel"] = &QSqlRelationalTableModel::relationModel;
    mt["setJoinMode"] = &QSqlRelationalTableModel::setJoinMode;
    mt["setRelation"] = &QSqlRelationalTableModel::setRelation;
}

} // namespace lua

int QSqlRelationalTableModel_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        lua::push(state, new QSqlRelationalTableModel);
        break;
    case 1:
        lua::push(state, new QSqlRelationalTableModel(
            lua::get<QObject*>(state, 1)
        ));
        break;
    case 2:
    default:
        lua::push(state, new QSqlRelationalTableModel(
            lua::get<QObject*>(state, 1),
            lua::get<QSqlDatabase>(state, 2)
        ));
        break;
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlRelationalTableModel(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlRelationalTableModel"] = lua::value::table;
    env["QSqlRelationalTableModel"]["new"] = QSqlRelationalTableModel_new;
    auto t = env["QSqlRelationalTableModel"];

    // enum QSqlRelationalTableModel::JoinMode
    t["InnerJoin"] = QSqlRelationalTableModel::InnerJoin;
    t["LeftJoin"] = QSqlRelationalTableModel::LeftJoin;

    return 0;
}

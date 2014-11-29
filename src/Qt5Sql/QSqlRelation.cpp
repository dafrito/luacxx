#include "QSqlRelation.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"

namespace lua {

void QSqlRelation_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["displayColumn"] = &QSqlRelation::displayColumn;
    mt["indexColumn"] = &QSqlRelation::indexColumn;
    mt["isValid"] = &QSqlRelation::isValid;
    mt["tableName"] = &QSqlRelation::tableName;
}

} // namespace lua

int QSqlRelation_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QSqlRelation()
        lua::make<QSqlRelation>(state);
    } else {
        // QSqlRelation(const QString & tableName, const QString & indexColumn, const QString & displayColumn)
        lua::make<QSqlRelation>(state,
            lua::get<QString>(state, 1),
            lua::get<QString>(state, 2),
            lua::get<QString>(state, 3)
        );
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlRelation(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlRelation"] = lua::value::table;
    env["QSqlRelation"]["new"] = QSqlRelation_new;
    auto t = env["QSqlRelation"];

    return 0;
}

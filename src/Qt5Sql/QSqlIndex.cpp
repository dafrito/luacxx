#include "QSqlIndex.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QSqlField.hpp"
#include "../Qt5Core/QString.hpp"

int QSqlIndex_append(lua_State* const state)
{
    auto self = lua::get<QSqlIndex*>(state, 1);
    if (lua_gettop(state) == 2) {
        self->append(
            lua::get<const QSqlField&>(state, 2)
        );
    } else {
        self->append(
            lua::get<const QSqlField&>(state, 2),
            lua::get<bool>(state, 3)
        );
    }
    return 1;
}

namespace lua {

void QSqlIndex_metatable(lua_State* const state, const int pos)
{
    lua::QSqlRecord_metatable(state, pos);

    lua::index mt(state, pos);
    mt["append"] = QSqlIndex_append;
    mt["cursorName"] = &QSqlIndex::cursorName;
    mt["isDescending"] = &QSqlIndex::isDescending;
    mt["name"] = &QSqlIndex::name;
    mt["setCursorName"] = &QSqlIndex::setCursorName;
    mt["setDescending"] = &QSqlIndex::setDescending;
    mt["setName"] = &QSqlIndex::setName;
}

} // namespace lua

int QSqlIndex_new(lua_State* const state)
{
    if (lua::is_type<QSqlIndex>(state, 1)) {
        // QSqlIndex(const QSqlIndex & other)
        lua::make<QSqlIndex>(state,
            lua::get<const QSqlIndex&>(state, 1)
        );
    } else {
        switch (lua_gettop(state)) {
        case 0:
            // QSqlIndex()
            lua::make<QSqlIndex>(state);
            break;
        case 1:
            // QSqlIndex(const QString & cursorname)
            lua::make<QSqlIndex>(state,
                lua::get<QString>(state, 1)
            );
            break;
        case 2:
        default:
            // QSqlIndex(const QString & cursorname, const QString & name)
            lua::make<QSqlIndex>(state,
                lua::get<QString>(state, 1),
                lua::get<QString>(state, 2)
            );
            break;
        }
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlIndex(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlIndex"] = lua::value::table;
    env["QSqlIndex"]["new"] = QSqlIndex_new;
    auto t = env["QSqlIndex"];

    return 0;
}

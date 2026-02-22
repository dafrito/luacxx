#include "QSqlRelationalDelegate.hpp"

#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QSqlRelationalDelegate_metatable(lua_State* const state, const int pos)
{
    lua::QItemDelegate_metatable(state, pos);
}

} // namespace lua

#ifdef QT_WIDGETS_LIB

int QSqlRelationalDelegate_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::push(state, new QSqlRelationalDelegate);
    } else {
        lua::push(state, new QSqlRelationalDelegate(lua::get<QObject*>(state, 1)));
    }

    return 1;
}

int luaopen_Qt5Sql_QSqlRelationalDelegate(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlRelationalDelegate"] = lua::value::table;
    env["QSqlRelationalDelegate"]["new"] = QSqlRelationalDelegate_new;
    auto t = env["QSqlRelationalDelegate"];

    return 0;
}

#endif // QT_WIDGETS_LIB

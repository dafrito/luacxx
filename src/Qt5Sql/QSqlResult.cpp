#include "QSqlResult.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QSqlDriver.hpp"
#include "QSqlResult.hpp"
#include "../Qt5Core/QVariant.hpp"

namespace lua {

void QSqlResult_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["handle"] = &QSqlResult::handle;
}

} // namespace lua

int luaopen_Qt5Sql_QSqlResult(lua_State* const state)
{
    lua::thread env(state);

    env["QSqlResult"] = lua::value::table;
    auto t = env["QSqlResult"];

    return 0;
}

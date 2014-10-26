#include "QPageSize.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QPageSize_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QPageSize_new(lua_State* const state)
{
    lua::make<QPageSize>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QPageSize(lua_State* const state)
{
    lua::thread env(state);

    env["QPageSize"] = lua::value::table;
    env["QPageSize"]["new"] = QPageSize_new;
    auto t = env["QPageSize"];

    return 0;
}

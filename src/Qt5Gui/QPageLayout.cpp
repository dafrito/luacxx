#include "QPageLayout.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QPageLayout_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QPageLayout_new(lua_State* const state)
{
    lua::make<QPageLayout>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QPageLayout(lua_State* const state)
{
    lua::thread env(state);

    env["QPageLayout"] = lua::value::table;
    env["QPageLayout"]["new"] = QPageLayout_new;
    auto t = env["QPageLayout"];

    return 0;
}

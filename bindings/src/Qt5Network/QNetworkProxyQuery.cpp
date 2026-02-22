#include "QNetworkProxyQuery.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkProxyQuery_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QNetworkProxyQuery_new(lua_State* const state)
{
    lua::make<QNetworkProxyQuery>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkProxyQuery(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkProxyQuery"] = lua::value::table;
    env["QNetworkProxyQuery"]["new"] = QNetworkProxyQuery_new;
    auto t = env["QNetworkProxyQuery"];

    return 0;
}

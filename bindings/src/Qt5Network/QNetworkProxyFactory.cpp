#include "QNetworkProxyFactory.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkProxyFactory_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int luaopen_luacxx_QNetworkProxyFactory(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkProxyFactory"] = lua::value::table;
    auto t = env["QNetworkProxyFactory"];

    return 0;
}

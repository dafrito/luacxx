#include "QNetworkConfiguration.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkConfiguration_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QNetworkConfiguration_new(lua_State* const state)
{
    lua::make<QNetworkConfiguration>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkConfiguration(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkConfiguration"] = lua::value::table;
    env["QNetworkConfiguration"]["new"] = QNetworkConfiguration_new;
    auto t = env["QNetworkConfiguration"];

    return 0;
}

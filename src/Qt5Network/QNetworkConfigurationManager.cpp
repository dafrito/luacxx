#include "QNetworkConfigurationManager.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkConfigurationManager_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QNetworkConfigurationManager_new(lua_State* const state)
{
    lua::make<QNetworkConfigurationManager>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkConfigurationManager(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkConfigurationManager"] = lua::value::table;
    env["QNetworkConfigurationManager"]["new"] = QNetworkConfigurationManager_new;
    auto t = env["QNetworkConfigurationManager"];

    return 0;
}

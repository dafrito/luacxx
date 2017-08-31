#include "QNetworkDiskCache.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkDiskCache_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QNetworkDiskCache_new(lua_State* const state)
{
    lua::make<QNetworkDiskCache>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkDiskCache(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkDiskCache"] = lua::value::table;
    env["QNetworkDiskCache"]["new"] = QNetworkDiskCache_new;
    auto t = env["QNetworkDiskCache"];

    return 0;
}

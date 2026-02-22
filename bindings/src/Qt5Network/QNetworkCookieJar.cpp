#include "QNetworkCookieJar.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkCookieJar_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QNetworkCookieJar_new(lua_State* const state)
{
    lua::make<QNetworkCookieJar>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkCookieJar(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkCookieJar"] = lua::value::table;
    env["QNetworkCookieJar"]["new"] = QNetworkCookieJar_new;
    auto t = env["QNetworkCookieJar"];

    return 0;
}

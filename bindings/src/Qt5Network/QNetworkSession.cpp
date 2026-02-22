#include "QNetworkSession.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkSession_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QNetworkSession_new(lua_State* const state)
{
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkSession(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkSession"] = lua::value::table;
    env["QNetworkSession"]["new"] = QNetworkSession_new;
    auto t = env["QNetworkSession"];

    return 0;
}

#include "QNetworkReply.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkReply_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QNetworkReply_new(lua_State* const state)
{
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkReply(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkReply"] = lua::value::table;
    env["QNetworkReply"]["new"] = QNetworkReply_new;
    auto t = env["QNetworkReply"];

    return 0;
}

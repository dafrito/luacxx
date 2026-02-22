#include "QNetworkCacheMetaData.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QNetworkCacheMetaData_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QNetworkCacheMetaData_new(lua_State* const state)
{
    lua::make<QNetworkCacheMetaData>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkCacheMetaData(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkCacheMetaData"] = lua::value::table;
    env["QNetworkCacheMetaData"]["new"] = QNetworkCacheMetaData_new;
    auto t = env["QNetworkCacheMetaData"];

    return 0;
}

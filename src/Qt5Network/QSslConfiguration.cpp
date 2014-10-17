#include "QSslConfiguration.hpp"
#include "../thread.hpp"

#include <QSslConfiguration>

void lua::QSslConfiguration_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

int QSslConfiguration_new(lua_State* const state)
{
    lua::make<QSslConfiguration>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QSslConfiguration(lua_State* const state)
{
    lua::thread env(state);

    env["QSslConfiguration"] = lua::value::table;
    env["QSslConfiguration"]["new"] = QSslConfiguration_new;
    auto t = env["QSslConfiguration"];

    return 0;
}

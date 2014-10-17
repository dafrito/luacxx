#include "QTimeZone.hpp"
#include "../thread.hpp"

void lua::QTimeZone_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

int QTimeZone_new(lua_State* const state)
{
    lua::make<QTimeZone>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QTimeZone(lua_State* const state)
{
    lua::thread env(state);

    env["QTimeZone"] = lua::value::table;
    env["QTimeZone"]["new"] = QTimeZone_new;
    auto t = env["QTimeZone"];

    return 0;
}

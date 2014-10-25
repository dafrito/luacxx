#include "QStyleOption.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QStyleOption_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QStyleOption_new(lua_State* const state)
{
    lua::make<QStyleOption>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Widgets_QStyleOption(lua_State* const state)
{
    lua::thread env(state);

    env["QStyleOption"] = lua::value::table;
    env["QStyleOption"]["new"] = QStyleOption_new;
    auto t = env["QStyleOption"];

    return 0;
}

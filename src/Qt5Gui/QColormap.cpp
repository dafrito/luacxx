#include "QColormap.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QColormap_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QColormap_new(lua_State* const state)
{
    lua::make<QColormap>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QColormap(lua_State* const state)
{
    lua::thread env(state);

    env["QColormap"] = lua::value::table;
    env["QColormap"]["new"] = QColormap_new;
    auto t = env["QColormap"];

    return 0;
}

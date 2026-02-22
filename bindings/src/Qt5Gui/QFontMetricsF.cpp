#include "QFontMetricsF.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QFontMetricsF_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QFontMetricsF_new(lua_State* const state)
{
    lua::make<QFontMetricsF>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QFontMetricsF(lua_State* const state)
{
    lua::thread env(state);

    env["QFontMetricsF"] = lua::value::table;
    env["QFontMetricsF"]["new"] = QFontMetricsF_new;
    auto t = env["QFontMetricsF"];

    return 0;
}

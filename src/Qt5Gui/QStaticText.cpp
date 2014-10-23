#include "QStaticText.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

void lua::QStaticText_metatable(lua_State* const state, const int mt)
{
    // TODO Set up metatable methods for this class
}

int QStaticText_new(lua_State* const state)
{
    lua::make<QStaticText>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QStaticText(lua_State* const state)
{
    lua::thread env(state);

    env["QStaticText"] = lua::value::table;
    env["QStaticText"]["new"] = QStaticText_new;
    auto t = env["QStaticText"];

    return 0;
}

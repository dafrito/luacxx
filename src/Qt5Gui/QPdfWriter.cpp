#include "QPdfWriter.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QPdfWriter_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int QPdfWriter_new(lua_State* const state)
{
    lua::make<QPdfWriter>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QPdfWriter(lua_State* const state)
{
    lua::thread env(state);

    env["QPdfWriter"] = lua::value::table;
    env["QPdfWriter"]["new"] = QPdfWriter_new;
    auto t = env["QPdfWriter"];

    return 0;
}

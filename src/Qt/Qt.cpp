#include "Qt.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

int luaopen_luacxx_Qt(lua_State* const state)
{
    lua::thread env(state);

    env["Qt"] = lua::value::table;
    auto t = env["Qt"];

    t["white"] = "Qt.White";
    t["black"] = "Qt.Black";

    return 0;
}

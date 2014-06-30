#include "../ncurses.hpp"
#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/legacy_coding.3x.html

void lua::ncurses_legacy_coding(lua_State* const state)
{
    lua::thread env(state);

    env["use_legacy_coding"] = use_legacy_coding;
}

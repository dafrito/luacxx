#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_delch.3x.html

void lua::ncurses_curs_delch(lua_State* const state)
{
    lua::thread env(state);

    env["delch"] = delch;
    env["wdelch"] = wdelch;
    env["mvdelch"] = mvdelch;
    env["mvwdelch"] = mvwdelch;
}

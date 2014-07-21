#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_get_wch.3x.html

void lua::ncurses_curs_get_wch(lua_State* const state)
{
    lua::thread env(state);

    env["get_wch"] = get_wch;
    env["wget_wch"] = wget_wch;
    env["mvget_wch"] = mvget_wch;
    env["mvwget_wch"] = mvwget_wch;
    env["unget_wch"] = unget_wch;
}

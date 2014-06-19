#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_scroll.3x.html

void lua::ncurses_curs_scroll(lua_State* const state)
{
    lua::thread env(state);

    env["scroll"] = scroll;
    env["scrl"] = scrl;
    env["wscrl"] = wscrl;
}

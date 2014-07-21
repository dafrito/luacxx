#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_overlay.3x.html

void lua::ncurses_curs_overlay(lua_State* const state)
{
    lua::thread env(state);

    env["overlay"] = overlay;
    env["overwrite"] = overwrite;
    env["copywin"] = copywin;
}

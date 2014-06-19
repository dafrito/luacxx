#include "../ncurses.hpp"
#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/wresize.3x.html

void lua::ncurses_wresize(lua_State* const state)
{
    lua::thread env(state);

    env["wresize"] = wresize;
}

#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_move.3x.html

void lua::ncurses_curs_move(lua_State* const state)
{
    lua::thread env(state);

    env["move"] = move;
    env["wmove"] = wmove;
}

#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_print.3x.html

void lua::ncurses_curs_print(lua_State* const state)
{
    lua::thread env(state);

    env["mcprint"] = mcprint;
}

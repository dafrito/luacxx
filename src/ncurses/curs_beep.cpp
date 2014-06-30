#include "../ncurses.hpp"
#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_beep.3x.html

void lua::ncurses_curs_beep(lua_State* const state)
{
    lua::thread env(state);

    env["beep"] = beep;
    env["flash"] = flash;
}

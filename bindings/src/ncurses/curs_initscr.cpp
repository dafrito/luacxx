#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_initscr.3x.html

void lua::ncurses_curs_initscr(lua_State* const state)
{
    lua::thread env(state);

    env["initscr"] = initscr;
    env["endwin"] = endwin;
    env["isendwin"] = isendwin;
    env["newterm"] = newterm;
    env["set_term"] = set_term;
    env["delscreen"] = delscreen;
}

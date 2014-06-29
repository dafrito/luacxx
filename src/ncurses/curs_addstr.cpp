#include "../ncurses.hpp"
#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_addstr.3x.html

void lua::ncurses_curs_addstr(lua_State* const state)
{
    lua::thread env(state);

    env["addstr"] = addstr;
    env["addnstr"] = addnstr;
    env["waddstr"] = waddstr;
    env["waddnstr"] = waddnstr;
    env["mvaddstr"] = mvaddstr;
    env["mvaddnstr"] = mvaddnstr;
    env["mvwaddstr"] = mvwaddstr;
    env["mvwaddnstr"] = mvwaddnstr;
}

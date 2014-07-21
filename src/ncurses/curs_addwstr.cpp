#include "../ncurses.hpp"
#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_addwstr.3x.html

void lua::ncurses_curs_addwstr(lua_State* const state)
{
    lua::thread env(state);

    env["addwstr"] = addwstr;
    env["addnwstr"] = addnwstr;
    env["waddwstr"] = waddwstr;
    env["waddnwstr"] = waddnwstr;
    env["mvaddwstr"] = mvaddwstr;
    env["mvaddnwstr"] = mvaddnwstr;
    env["mvwaddwstr"] = mvwaddwstr;
    env["mvwaddnwstr"] = mvwaddnwstr;
}

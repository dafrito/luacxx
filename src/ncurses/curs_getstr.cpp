#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_getstr.3x.html

void lua::ncurses_curs_getstr(lua_State* const state)
{
    lua::thread env(state);

    env["getstr"] = getstr;
    env["getnstr"] = getnstr;
    env["wgetstr"] = wgetstr;
    env["wgetnstr"] = wgetnstr;
    env["mvgetstr"] = mvgetstr;
    env["mvwgetstr"] = mvwgetstr;
    env["mvgetnstr"] = mvgetnstr;
    env["mvwgetnstr"] = mvwgetnstr;
}

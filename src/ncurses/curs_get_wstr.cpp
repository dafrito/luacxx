#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_get_wstr.3x.html

void lua::ncurses_curs_get_wstr(lua_State* const state)
{
    lua::thread env(state);

    env["get_wstr"] = get_wstr;
    env["getn_wstr"] = getn_wstr;
    env["wget_wstr"] = wget_wstr;
    env["wgetn_wstr"] = wgetn_wstr;
    env["mvget_wstr"] = mvget_wstr;
    env["mvgetn_wstr"] = mvgetn_wstr;
    env["mvwget_wstr"] = mvwget_wstr;
    env["mvwgetn_wstr"] = mvwgetn_wstr;
}

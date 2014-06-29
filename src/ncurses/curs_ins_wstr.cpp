#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_ins_wstr.3x.html

void lua::ncurses_curs_ins_wstr(lua_State* const state)
{
    lua::thread env(state);

    env["ins_wstr"] = ins_wstr;
    env["ins_nwstr"] = ins_nwstr;
    env["wins_wstr"] = wins_wstr;
    env["wins_nwstr"] = wins_nwstr;
    env["mvins_wstr"] = mvins_wstr;
    env["mvins_nwstr"] = mvins_nwstr;
    env["mvwins_wstr"] = mvwins_wstr;
    env["mvwins_nwstr"] = mvwins_nwstr;
}

#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_ins_wch.3x.html

void lua::ncurses_curs_ins_wch(lua_State* const state)
{
    lua::thread env(state);

    env["ins_wch"] = std::function<int(cchar_t *)>(ins_wch);
    env["wins_wch"] = std::function<int(WINDOW *, cchar_t *)>(wins_wch);
    env["mvins_wch"] = std::function<int(int, int, cchar_t *)>(mvins_wch);
    env["mvwins_wch"] = std::function<int(WINDOW *, int, int, cchar_t *)>(mvwins_wch);
}

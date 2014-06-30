#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_in_wch.3x.html

void lua::ncurses_curs_in_wch(lua_State* const state)
{
    lua::thread env(state);

    env["in_wch"] = std::function<int(cchar_t*)>(in_wch);
    env["mvin_wch"] = std::function<int(int, int, cchar_t*)>(mvin_wch);
    env["mvwin_wch"] = std::function<int(WINDOW *, int, int, cchar_t*)>(mvwin_wch);
    env["win_wch"] = std::function<int(WINDOW *win, cchar_t*)>(win_wch);
}

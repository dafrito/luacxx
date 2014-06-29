#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_in_wchstr.3x.html

void lua::ncurses_curs_in_wchstr(lua_State* const state)
{
    lua::thread env(state);

    env["in_wchstr"] = std::function<int(cchar_t*)>(in_wchstr);
    env["in_wchnstr"] = std::function<int(cchar_t*, int)>(in_wchnstr);
    env["win_wchstr"] = std::function<int(WINDOW *, cchar_t*)>(win_wchstr);
    env["win_wchnstr"] = std::function<int(WINDOW *, cchar_t*, int)>(win_wchnstr);
    env["mvin_wchstr"] = std::function<int(int, int, cchar_t*)>(mvin_wchstr);
    env["mvin_wchnstr"] = std::function<int(int, int, cchar_t*, int)>(mvin_wchnstr);
    env["mvwin_wchstr"] = std::function<int(WINDOW *win, int, int, cchar_t* w)>(mvwin_wchstr);
    env["mvwin_wchnstr"] = std::function<int(WINDOW *win, int, int, cchar_t* w, int n)>(mvwin_wchnstr);
}

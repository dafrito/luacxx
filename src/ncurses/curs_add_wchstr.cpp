#include "../ncurses.hpp"
#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_add_wchstr.3x.html

void lua::ncurses_curs_add_wchstr(lua_State* const state)
{
    lua::thread env(state);

    env["add_wchstr"] = std::function<int (cchar_t *)>(add_wchstr);
    env["add_wchnstr"] = std::function<int (cchar_t *, int)>(add_wchnstr);
    env["wadd_wchstr"] = std::function<int (WINDOW *, cchar_t *)>(wadd_wchstr);
    env["wadd_wchnstr"] = std::function<int (WINDOW *, cchar_t *, int)>(wadd_wchnstr);
    env["mvadd_wchstr"] = std::function<int (int, int, cchar_t *)>(mvadd_wchstr);
    env["mvadd_wchnstr"] = std::function<int (int, int, cchar_t *, int)>(mvadd_wchnstr);
    env["mvwadd_wchstr"] = std::function<int (WINDOW *, int, int, cchar_t *)>(mvwadd_wchstr);
    env["mvwadd_wchnstr"] = std::function<int (WINDOW *, int, int, cchar_t *, int)>(mvwadd_wchnstr);
}

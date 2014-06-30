#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_inchstr.3x.html

void lua::ncurses_curs_inchstr(lua_State* const state)
{
    lua::thread env(state);

    env["inchstr"] = std::function<int(chtype *)>(inchstr);
    env["inchnstr"] = std::function<int(chtype *, int)>(inchnstr);
    env["winchstr"] = std::function<int(WINDOW *, chtype *)>(winchstr);
    env["winchnstr"] = std::function<int(WINDOW *, chtype *, int)>(winchnstr);
    env["mvinchstr"] = std::function<int(int, int, chtype *)>(mvinchstr);
    env["mvinchnstr"] = std::function<int(int, int, chtype *, int)>(mvinchnstr);
    env["mvwinchstr"] = std::function<int(WINDOW *, int, int, chtype *)>(mvwinchstr);
    env["mvwinchnstr"] = std::function<int(WINDOW *, int, int, chtype *, int)>(mvwinchnstr);
}

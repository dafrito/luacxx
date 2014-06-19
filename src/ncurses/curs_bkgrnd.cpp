#include "../ncurses.hpp"
#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_bkgrnd.3x.html

void lua::ncurses_curs_bkgrnd(lua_State* const state)
{
    lua::thread env(state);

    env["bkgrnd"] = std::function<int( cchar_t *)>(bkgrnd);
    env["wbkgrnd"] = std::function<int( WINDOW *, cchar_t *)>(wbkgrnd);
    env["bkgrndset"] = std::function<void(cchar_t *)>(bkgrndset);
    env["wbkgrndset"] = std::function<void(WINDOW *win, cchar_t *)>(wbkgrndset);
    env["getbkgrnd"] = std::function<int(cchar_t *)>(getbkgrnd);
    env["wgetbkgrnd"] = std::function<int(WINDOW *, cchar_t *)>(wgetbkgrnd);
}

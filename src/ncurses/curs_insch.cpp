#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_insch.3x.html

void lua::ncurses_curs_insch(lua_State* const state)
{
    lua::thread env(state);

    env["insch"] = std::function<int(chtype)>(insch);
    env["winsch"] = std::function<int(WINDOW *, chtype)>(winsch);
    env["mvinsch"] = std::function<int(int, int, chtype)>(mvinsch);
    env["mvwinsch"] = std::function<int(WINDOW *, int, int, chtype)>(mvwinsch);
}

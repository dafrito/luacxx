#include "../ncurses.hpp"
#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_bkgd.3x.html

void lua::ncurses_curs_bkgd(lua_State* const state)
{
    lua::thread env(state);

    env["bkgdset"] = std::function<void (chtype)>(bkgdset);
    env["wbkgdset"] = std::function<void (WINDOW *, chtype)>(wbkgdset);
    env["bkgd"] = std::function<int (chtype)>(bkgd);
    env["wbkgd"] = std::function<int (WINDOW *, chtype)>(wbkgd);
    env["getbkgd"] = std::function<chtype (WINDOW *)>(getbkgd);
}

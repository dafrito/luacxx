#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_refresh.3x.html

void lua::ncurses_curs_refresh(lua_State* const state)
{
    lua::thread env(state);

    env["refresh"] = refresh;
    env["wrefresh"] = wrefresh;
    env["wnoutrefresh"] = wnoutrefresh;
    env["doupdate"] = doupdate;
    env["redrawwin"] = redrawwin;
    env["wredrawln"] = wredrawln;
}

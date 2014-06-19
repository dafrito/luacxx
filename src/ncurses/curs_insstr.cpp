#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_insstr.3x.html

void lua::ncurses_curs_insstr(lua_State* const state)
{
    lua::thread env(state);

    env["insstr"] = insstr;
    env["insnstr"] = insnstr;
    env["winsstr"] = winsstr;
    env["winsnstr"] = winsnstr;
    env["mvinsstr"] = mvinsstr;
    env["mvinsnstr"] = mvinsnstr;
    env["mvwinsstr"] = mvwinsstr;
    env["mvwinsnstr"] = mvwinsnstr;
}

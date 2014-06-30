#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_inwstr.3x.html

void lua::ncurses_curs_inwstr(lua_State* const state)
{
    lua::thread env(state);

    env["inwstr"] = inwstr;
    env["innwstr"] = innwstr;
    env["winwstr"] = winwstr;
    env["winnwstr"] = winnwstr;
    env["mvinwstr"] = mvinwstr;
    env["mvinnwstr"] = mvinnwstr;
    env["mvwinwstr"] = mvwinwstr;
    env["mvwinnwstr"] = mvwinnwstr;
}

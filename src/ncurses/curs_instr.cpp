#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_instr.3x.html

void lua::ncurses_curs_instr(lua_State* const state)
{
    lua::thread env(state);

    env["instr"] = std::function<int(char *)>(instr);
    env["innstr"] = std::function<int(char *, int)>(innstr);
    env["winstr"] = std::function<int(WINDOW *, char *)>(winstr);
    env["winnstr"] = std::function<int(WINDOW *, char *, int)>(winnstr);
    env["mvinstr"] = std::function<int(int, int, char *)>(mvinstr);
    env["mvinnstr"] = std::function<int(int, int, char *, int)>(mvinnstr);
    env["mvwinstr"] = std::function<int(WINDOW *, int, int, char *)>(mvwinstr);
    env["mvwinnstr"] = std::function<int (WINDOW *, int, int, char *, int)>(mvwinnstr);
}

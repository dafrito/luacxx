#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_deleteln.3x.html

void lua::ncurses_curs_deleteln(lua_State* const state)
{
    lua::thread env(state);

    env["deleteln"] = deleteln;
    env["wdeleteln"] = wdeleteln;
    env["insdelln"] = insdelln;
    env["winsdelln"] = winsdelln;
    env["insertln"] = insertln;
    env["winsertln"] = winsertln;
}

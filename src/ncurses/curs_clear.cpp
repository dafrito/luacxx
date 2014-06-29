#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_clear.3x.html

void lua::ncurses_curs_clear(lua_State* const state)
{
    lua::thread env(state);

    env["erase"] = erase;
    env["werase"] = werase;
    env["clear"] = ::clear;
    env["wclear"] = wclear;
    env["clrtobot"] = clrtobot;
    env["wclrtobot"] = wclrtobot;
    env["clrtoeol"] = clrtoeol;
    env["wclrtoeol"] = wclrtoeol;
}

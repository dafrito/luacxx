#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_legacy.3x.html

void lua::ncurses_curs_legacy(lua_State* const state)
{
    lua::thread env(state);

    env["getattrs"] = getattrs;
    env["getbegx"] = getbegx;
    env["getbegy"] = getbegy;
    env["getcurx"] = getcurx;
    env["getcury"] = getcury;
    env["getmaxx"] = getmaxx;
    env["getmaxy"] = getmaxy;
    env["getparx"] = getparx;
    env["getpary"] = getpary;
}

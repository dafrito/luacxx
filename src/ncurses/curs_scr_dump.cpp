#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_scr_dump.3x.html

void lua::ncurses_curs_scr_dump(lua_State* const state)
{
    lua::thread env(state);

    env["scr_dump"] = scr_dump;
    env["scr_restore"] = scr_restore;
    env["scr_init"] = scr_init;
    env["scr_set"] = scr_set;
}

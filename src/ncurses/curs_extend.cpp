#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_extend.3x.html

void lua::ncurses_curs_extend(lua_State* const state)
{
    lua::thread env(state);

    env["curses_version"] = curses_version;
    env["use_extended_names"] = use_extended_names;
}

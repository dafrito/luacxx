#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/default_colors.3x.html

void lua::ncurses_default_colors(lua_State* const state)
{
    lua::thread env(state);

    env["use_default_colors"] = use_default_colors;
    env["assume_default_colors"] = assume_default_colors;
}

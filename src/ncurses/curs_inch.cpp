#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_inch.3x.html

void lua::ncurses_curs_inch(lua_State* const state)
{
    lua::thread env(state);

    env["inch"] = std::function<chtype(void)>(inch);
    env["winch"] = std::function<chtype(WINDOW *)>(winch);
    env["mvinch"] = std::function<chtype(int, int)>(mvinch);
    env["mvwinch"] = std::function<chtype(WINDOW *, int, int)>(mvwinch);

    env["A_CHARTEXT"] = A_CHARTEXT;
    env["A_ATTRIBUTES"] = A_ATTRIBUTES;
    env["A_COLOR"] = A_COLOR;
}

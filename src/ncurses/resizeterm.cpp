#include "../ncurses.hpp"
#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/resizeterm.3x.html

void lua::ncurses_resizeterm(lua_State* const state)
{
    lua::thread env(state);

    env["is_term_resized"] = is_term_resized;
    env["resize_term"] = resize_term;
    env["resizeterm"] = resizeterm;
}

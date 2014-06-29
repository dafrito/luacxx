#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/keybound.3x.html

void lua::ncurses_keybound(lua_State* const state)
{
    lua::thread env(state);

    env["keybound"] = keybound;
}

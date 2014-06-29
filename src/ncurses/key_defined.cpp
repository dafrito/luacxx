#include "../ncurses.hpp"
#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/key_defined.3x.html

void lua::ncurses_key_defined(lua_State* const state)
{
    lua::thread env(state);

    env["key_defined"] = key_defined;
}

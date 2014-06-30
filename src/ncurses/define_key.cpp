#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/define_key.3x.html

void lua::ncurses_define_key(lua_State* const state)
{
    lua::thread env(state);

    env["define_key"] = define_key;
}

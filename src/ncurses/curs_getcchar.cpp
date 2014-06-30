#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_getcchar.3x.html

void lua::ncurses_curs_getcchar(lua_State* const state)
{
    lua::thread env(state);

    env["getcchar"] = getcchar; // std::function<int(const cchar_t*, wchar_t*, attr_t, short*, void*)>(getcchar);
    env["setcchar"] = setcchar; // std::function<int(cchar_t*, const wchar_t*, attr_t, short, void*)>(setcchar);
}

#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_pad.3x.html

void lua::ncurses_curs_pad(lua_State* const state)
{
    lua::thread env(state);

    env["newpad"] = newpad;
    env["subpad"] = subpad;
    env["prefresh"] = prefresh;
    env["pnoutrefresh"] = pnoutrefresh;
    env["pechochar"] = std::function<int(WINDOW*, chtype)>(pechochar);
    env["pecho_wchar"] = std::function<int(WINDOW*, const cchar_t*)>(pecho_wchar);
}

#include "../ncurses.hpp"
#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_addch.3x.html

void lua::ncurses_curs_addch(lua_State* const state)
{
    lua::thread env(state);

    env["addch"] = std::function<int(const chtype)>(addch);
    env["waddch"] = std::function<int(WINDOW*, const chtype)>(waddch);
    env["mvaddch"] = std::function<int(int, int, const chtype)>(mvaddch);
    env["mvwaddch"] = std::function<int(WINDOW*, int, int, const chtype)>(mvwaddch);
    env["echochar"] = std::function<int(const chtype)>(echochar);
    env["wechochar"] = std::function<int(WINDOW*, const chtype)>(wechochar);
}

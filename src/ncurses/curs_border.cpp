#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_border.3x.html

void lua::ncurses_curs_border(lua_State* const state)
{
    lua::thread env(state);

    env["border"] = std::function<int (chtype, chtype, chtype, chtype, chtype, chtype, chtype, chtype)>(border);
    env["wborder"] = std::function<int (WINDOW *, chtype, chtype, chtype, chtype, chtype, chtype, chtype, chtype)>(wborder);
    env["box"] = std::function<int (WINDOW *, chtype, chtype)>(box);
    env["hline"] = std::function<int (chtype, int)>(hline);
    env["whline"] = std::function<int (WINDOW *, chtype, int)>(whline);
    env["vline"] = std::function<int (chtype, int)>(vline);
    env["wvline"] = std::function<int (WINDOW *, chtype, int)>(wvline);
    env["mvhline"] = std::function<int (int, int, chtype, int)>(mvhline);
    env["mvwhline"] = std::function<int (WINDOW *, int, int, chtype, int)>(mvwhline);
    env["mvvline"] = std::function<int (int, int, chtype, int)>(mvvline);
    env["mvwvline"] = std::function<int (WINDOW *, int, int, chtype, int)>(mvwvline);
}

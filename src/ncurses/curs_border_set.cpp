#include "../ncurses.hpp"
#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_border_set.3x.html

void lua::ncurses_curs_border_set(lua_State* const state)
{
    lua::thread env(state);

    env["border_set"] = border_set;
    env["wborder_set"] = wborder_set;
    env["box_set"] = box_set;
    /*env["hline_set"] = std::function<int(cchar_t *, int)>(hline_set);
    env["whline_set"] = std::function<int(WINDOW*, cchar_t *, int)>(whline_set);
    env["mvhline_set"] = std::function<int(int, int, cchar_t *, int)>(mvhline_set);
    env["mvwhline_set"] = std::function<int(WINDOW*, int, int, cchar_t *, int)>(mvwhline_set);
    env["vline_set"] = std::function<int(cchar_t *, int)>(vline_set);
    env["wvline_set"] = std::function<int(WINDOW*, cchar_t *, int)>(wvline_set);
    env["mvvline_set"] = std::function<int(int, int, cchar_t *, int)>(mvvline_set);
    env["mvwvline_set"] = std::function<int(WINDOW*, int, int, cchar_t *, int)>(mvwvline_set);*/
}

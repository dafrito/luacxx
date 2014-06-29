#include "../ncurses.hpp"
#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_add_wch.3x.html

void lua::ncurses_curs_add_wch(lua_State* const state)
{
    lua::thread env(state);

    env["add_wch"] = std::function<int(cchar_t*)>(add_wch);
    env["wadd_wch"] = std::function<int(WINDOW*, cchar_t*)>(wadd_wch);
    env["mvadd_wch"] = std::function<int(int, int, const cchar_t*)>(mvadd_wch);
    env["mvwadd_wch"] = std::function<int(WINDOW*, int, int, cchar_t*)>(mvwadd_wch);
    env["echo_wchar"] = std::function<int(cchar_t*)>(echo_wchar);
    env["wecho_wchar"] = std::function<int(WINDOW*, cchar_t*)>(wecho_wchar);
}

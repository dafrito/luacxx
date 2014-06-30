#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_window.3x.html

void lua::ncurses_curs_window(lua_State* const state)
{
    lua::thread env(state);

    env["newwin"] = newwin;
    env["delwin"] = delwin;
    env["mvwin"] = mvwin;
    env["subwin"] = subwin;
    env["derwin"] = derwin;
    env["mvderwin"] = mvderwin;
    env["dupwin"] = dupwin;
    env["wsyncup"] = wsyncup;
    env["syncok"] = syncok;
    env["wcursyncup"] = wcursyncup;
    env["wsyncdown"] = wsyncdown;
}

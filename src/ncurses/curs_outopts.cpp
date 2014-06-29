#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_outopts.3x.html

void lua::ncurses_curs_outopts(lua_State* const state)
{
    lua::thread env(state);

    env["clearok"] = clearok;
    env["idlok"] = idlok;
    env["idcok"] = idcok;
    env["immedok"] = immedok;
    env["leaveok"] = leaveok;
    env["setscrreg"] = setscrreg;
    env["wsetscrreg"] = wsetscrreg;
    env["scrollok"] = scrollok;
    env["nl"] = nl;
    env["nonl"] = nonl;
}

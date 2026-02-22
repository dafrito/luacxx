#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_touch.3x.html

void lua::ncurses_curs_touch(lua_State* const state)
{
    lua::thread env(state);

    env["touchwin"] = touchwin;
    env["touchline"] = touchline;
    env["untouchwin"] = untouchwin;
    env["wtouchln"] = wtouchln;
    env["is_linetouched"] = is_linetouched;
    env["is_wintouched"] = is_wintouched;
}

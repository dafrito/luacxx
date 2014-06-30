#include "../ncurses.hpp"
#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_addchstr.3x.html

void lua::ncurses_curs_addchstr(lua_State* const state)
{
    lua::thread env(state);

    env["addchstr"] = std::function<int(chtype*)>(addchstr);
    env["addchnstr"] = std::function<int(chtype*, int)>(addchnstr);
    env["waddchstr"] = std::function<int(WINDOW*, chtype*)>(waddchstr);
    env["waddchnstr"] = std::function<int(WINDOW*, chtype*, int)>(waddchnstr);
    env["mvaddchstr"] = std::function<int(int, int, chtype*)>(mvaddchstr);
    env["mvaddchnstr"] = std::function<int(int, int, chtype*, int)>(mvaddchnstr);
    env["mvwaddchstr"] = std::function<int(WINDOW*, int, int, chtype*)>(mvwaddchstr);
    env["mvwaddchnstr"] = std::function<int(WINDOW*, int, int, chtype*, int)>(mvwaddchnstr);
}

#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_scanw.3x.html

void lua::ncurses_curs_scanw(lua_State* const state)
{
    lua::thread env(state);

    int scanw(char *fmt, ...);
    int wscanw(WINDOW *win, char *fmt, ...);
    int mvscanw(int y, int x, char *fmt, ...);
    int mvwscanw(WINDOW *win, int y, int x, char *fmt, ...);
    int vw_scanw(WINDOW *win, char *fmt, va_list varglist);
    int vwscanw(WINDOW *win, char *fmt, va_list varglist);
}

#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_printw.3x.html

void lua::ncurses_curs_printw(lua_State* const state)
{
    lua::thread env(state);

    // TODO
    // int printw(const char *fmt, ...);
    // int wprintw(WINDOW *win, const char *fmt, ...);
    // int mvprintw(int y, int x, const char *fmt, ...);
    // int mvwprintw(WINDOW *win, int y, int x, const char  *fmt, ...);
    // int  vwprintw(WINDOW  *win,  const char *fmt, va_list var- glist);
    // int vw_printw(WINDOW *win, const char *fmt,  va_list  var- glist);
}

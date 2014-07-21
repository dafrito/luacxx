#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_termattrs.3x.html

void lua::ncurses_curs_termattrs(lua_State* const state)
{
    lua::thread env(state);

    env["baudrate"] = baudrate;
    env["erasechar"] = erasechar;
    env["erasewchar"] = erasewchar;
    env["has_ic"] = has_ic;
    env["has_il"] = has_il;
    env["killchar"] = killchar;
    env["baudrate"] = baudrate;
    env["erasechar"] = erasechar;
    env["erasewchar"] = erasewchar;
    env["has_ic"] = has_ic;
    env["has_il"] = has_il;
    env["killchar"] = killchar;
    env["killwchar"] = killwchar;
    env["longname"] = longname;
    env["term_attrs"] = std::function<attr_t(void)>(term_attrs);
    env["termattrs"] = std::function<chtype(void)>(termattrs);
    env["termname"] = termname;
}

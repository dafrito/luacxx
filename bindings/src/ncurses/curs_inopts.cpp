#include "../ncurses.hpp"

#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_inopts.3x.html

void lua::ncurses_curs_inopts(lua_State* const state)
{
    lua::thread env(state);

    env["cbreak"] = cbreak;
    env["nocbreak"] = nocbreak;
    env["echo"] = echo;
    env["noecho"] = noecho;
    env["halfdelay"] = halfdelay;
    env["intrflush"] = intrflush;
    env["keypad"] = keypad;
    env["meta"] = meta;
    env["nodelay"] = nodelay;
    env["raw"] = raw;
    env["noraw"] = noraw;
    env["noqiflush"] = noqiflush;
    env["qiflush"] = qiflush;
    env["notimeout"] = notimeout;
    env["timeout"] = timeout;
    env["wtimeout"] = wtimeout;
    env["typeahead"] = typeahead;
}

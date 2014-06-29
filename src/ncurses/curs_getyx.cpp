#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_getyx.3x.html

int _getyx(lua_State* const state)
{
    int y, x;
    getyx(lua::get<WINDOW*>(state, 1), y, x);
    lua::push(state, y);
    lua::push(state, x);
    return 2;
}

int _getparyx(lua_State* const state)
{
    int y, x;
    getparyx(lua::get<WINDOW*>(state, 1), y, x);
    lua::push(state, y);
    lua::push(state, x);
    return 2;
}

int _getbegyx(lua_State* const state)
{
    int y, x;
    getbegyx(lua::get<WINDOW*>(state, 1), y, x);
    lua::push(state, y);
    lua::push(state, x);
    return 2;
}

int _getmaxyx(lua_State* const state)
{
    int y, x;
    getmaxyx(lua::get<WINDOW*>(state, 1), y, x);
    lua::push(state, y);
    lua::push(state, x);
    return 2;
}

void lua::ncurses_curs_getyx(lua_State* const state)
{
    lua::thread env(state);

    env["getyx"] = _getyx;
    env["getparyx"] = _getparyx;
    env["getbegyx"] = _getbegyx;
    env["getmaxyx"] = _getmaxyx;
}

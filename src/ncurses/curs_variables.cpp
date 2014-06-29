#include "../ncurses.hpp"

#include "../lua-cxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_variables.3x.html

int _COLOR_PAIRS(lua_State* const state)
{
    lua::push(state, COLOR_PAIRS);
    return 1;
}

int _COLORS(lua_State* const state)
{
    lua::push(state, COLORS);
    return 1;
}

int _COLS(lua_State* const state)
{
    lua::push(state, COLS);
    return 1;
}

int _ESCDELAY(lua_State* const state)
{
    lua::push(state, ESCDELAY);
    return 1;
}

int _LINES(lua_State* const state)
{
    lua::push(state, LINES);
    return 1;
}

int _TABSIZE(lua_State* const state)
{
    lua::push(state, TABSIZE);
    return 1;
}

int _curscr(lua_State* const state)
{
    lua::push(state, curscr);
    return 1;
}

int _newscr(lua_State* const state)
{
    lua::push(state, newscr);
    return 1;
}

int _stdscr(lua_State* const state)
{
    lua::push(state, stdscr);
    return 1;
}

void lua::ncurses_curs_variables(lua_State* const state)
{
    lua::thread env(state);

    env["COLOR_PAIRS"] = _COLOR_PAIRS;
    env["COLORS"] = _COLORS;
    env["COLS"] = _COLS;
    env["ESCDELAY"] = _ESCDELAY;
    env["LINES"] = _LINES;
    env["TABSIZE"] = _TABSIZE;
    env["curscr"] = _curscr;
    env["newscr"] = _newscr;
    env["stdscr"] = _stdscr;
}

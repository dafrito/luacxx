#include "../ncurses.hpp"
#include "../thread.hpp"
#include "../reference.hpp"

#include <unordered_map>

// http://invisible-island.net/ncurses/man/curs_kernel.3x.html

std::unordered_map<WINDOW*, lua::reference> handlers;

int _ripoffline_handler(WINDOW* win, int cols)
{
    lua::reference& handler = handlers[win];
    if (handler) {
        return lua::call<int>(handler, win, cols);
    }
    return 0;
}

// int ripoffline(int line, int (*init)(WINDOW *, int));
int _ripoffline(lua_State* const state)
{
    handlers[lua::get<WINDOW*>(state, 2)] = lua::get<lua::reference>(state, 3);

    lua::push(state, ripoffline(
        lua::get<int>(state, 1),
        _ripoffline_handler
    ));
    return 1;
}

int _getsyx(lua_State* const state)
{
    int y, x;
    getsyx(y, x);
    lua::push(state, y, x);
    return 2;
}

int _setsyx(lua_State* const state)
{
    int y, x;
    y = lua::get<int>(state, 1);
    x = lua::get<int>(state, 2);
    setsyx(y, x);
    return 0;
}

void lua::ncurses_curs_kernel(lua_State* const state)
{
    lua::thread env(state);

    env["def_prog_mode"] = def_prog_mode;
    env["def_shell_mode"] = def_shell_mode;
    env["reset_prog_mode"] = reset_prog_mode;
    env["reset_shell_mode"] = reset_shell_mode;
    env["resetty"] = resetty;
    env["savetty"] = savetty;
    env["getsyx"] = _getsyx;
    env["setsyx"] = _setsyx;
    env["ripoffline"] = _ripoffline;
    env["curs_set"] = curs_set;
    env["napms"] = napms;
}

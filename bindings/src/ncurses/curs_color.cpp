#include "../ncurses.hpp"
#include "../thread.hpp"

// http://invisible-island.net/ncurses/man/curs_color.3x.html

int _color_content(lua_State* const state)
{
    short r, g, b;
    lua::push(state, color_content(lua::get<short>(state, 1), &r, &g, &b));
    lua::push(state, r);
    lua::push(state, g);
    lua::push(state, b);
    return 4;
}

int _pair_content(lua_State* const state)
{
    short f, b;
    lua::push(state, pair_content(lua::get<short>(state, 1), &f, &b));
    lua::push(state, f);
    lua::push(state, b);
    return 3;
}

void lua::ncurses_curs_color(lua_State* const state)
{
    lua::thread env(state);

    // COLOR_PAIR is defined in curs_attr

    env["start_color"] = start_color;
    env["init_pair"] = init_pair;
    env["init_color"] = init_color;
    env["has_colors"] = has_colors;
    env["can_change_color"] = can_change_color;
    env["color_content"] = _color_content;
    env["pair_content"] = _pair_content;

    env["COLOR_BLACK"] = COLOR_BLACK;
    env["COLOR_RED"] = COLOR_RED;
    env["COLOR_GREEN"] = COLOR_GREEN;
    env["COLOR_YELLOW"] = COLOR_YELLOW;
    env["COLOR_BLUE"] = COLOR_BLUE;
    env["COLOR_MAGENTA"] = COLOR_MAGENTA;
    env["COLOR_CYAN"] = COLOR_CYAN;
    env["COLOR_WHITE"] = COLOR_WHITE;
}

#include "../ncurses.hpp"

#include "../thread.hpp"


/*

=head1 NAME

curs_mouse - http://invisible-island.net/ncurses/man/curs_mouse.3x.html

=head1 SYNOPSIS

    require "luacxx.ncurses";

    initscr();
    noecho();
    keypad(stdscr(), TRUE);
    curs_set(0);

    mouseinterval(0);
    mousemask(ALL_MOUSE_EVENTS, nil);

    local y, x;

    while true do
        local ch = getch();
        if ch == KEY_MOUSE then
            local event = getmouse();
            y = event.y;
            x = event.x;
        elseif ch == KEY_DOWN then
            y = y + 1;
        elseif ch == KEY_RIGHT then
            x = x + 1;
        elseif ch == KEY_LEFT then
            x = x - 1;
        elseif ch == KEY_UP then
            y = y - 1;
        else
            endwin();
            break;
        end;

        if y ~= nil then
            mvaddstr(y, x, "*");
            refresh();
        end;
    end;
*/

int _getmouse(lua_State* const state)
{
    lua_settop(state, 0);
    MEVENT* event = lua::make<MEVENT>(state);
    getmouse(event);
    return 1;
}

int _mouse_trafo(lua_State* const state)
{
    int y, x;
    y = lua::get<int>(state, 1);
    x = lua::get<int>(state, 2);

    lua::push(state, mouse_trafo(&y, &x, lua::get<bool>(state, 3)));
    lua::push(state, y);
    lua::push(state, x);
    return 3;
}

int _wmouse_trafo(lua_State* const state)
{
    auto win = lua::get<WINDOW*>(state, 1);
    int y, x;
    y = lua::get<int>(state, 2);
    x = lua::get<int>(state, 3);

    lua::push(state, wmouse_trafo(win, &y, &x, lua::get<bool>(state, 3)));
    lua::push(state, y);
    lua::push(state, x);
    return 3;
}

void lua::ncurses_curs_mouse(lua_State* const state)
{
    lua::thread env(state);

    env["has_mouse"] = has_mouse;
    env["getmouse"] = _getmouse;
    env["ungetmouse"] = ungetmouse;
    env["mousemask"] = std::function<chtype(chtype, chtype*)>(mousemask);
    env["wenclose"] = wenclose;
    env["mouse_trafo"] = _mouse_trafo;
    env["wmouse_trafo"] = _wmouse_trafo;
    env["mouseinterval"] = mouseinterval;

    env["BUTTON1_PRESSED"] = BUTTON1_PRESSED;
    env["BUTTON1_RELEASED"] = BUTTON1_RELEASED;
    env["BUTTON1_CLICKED"] = BUTTON1_CLICKED;
    env["BUTTON1_DOUBLE_CLICKED"] = BUTTON1_DOUBLE_CLICKED;
    env["BUTTON1_TRIPLE_CLICKED"] = BUTTON1_TRIPLE_CLICKED;

    env["BUTTON2_PRESSED"] = BUTTON2_PRESSED;
    env["BUTTON2_RELEASED"] = BUTTON2_RELEASED;
    env["BUTTON2_CLICKED"] = BUTTON2_CLICKED;
    env["BUTTON2_DOUBLE_CLICKED"] = BUTTON2_DOUBLE_CLICKED;
    env["BUTTON2_TRIPLE_CLICKED"] = BUTTON2_TRIPLE_CLICKED;

    env["BUTTON3_PRESSED"] = BUTTON3_PRESSED;
    env["BUTTON3_RELEASED"] = BUTTON3_RELEASED;
    env["BUTTON3_CLICKED"] = BUTTON3_CLICKED;
    env["BUTTON3_DOUBLE_CLICKED"] = BUTTON3_DOUBLE_CLICKED;
    env["BUTTON3_TRIPLE_CLICKED"] = BUTTON3_TRIPLE_CLICKED;

    env["BUTTON4_PRESSED"] = BUTTON4_PRESSED;
    env["BUTTON4_RELEASED"] = BUTTON4_RELEASED;
    env["BUTTON4_CLICKED"] = BUTTON4_CLICKED;
    env["BUTTON4_DOUBLE_CLICKED"] = BUTTON4_DOUBLE_CLICKED;
    env["BUTTON4_TRIPLE_CLICKED"] = BUTTON4_TRIPLE_CLICKED;

    #ifdef BUTTON5_PRESSED
    env["BUTTON5_PRESSED"] = BUTTON5_PRESSED;
    env["BUTTON5_RELEASED"] = BUTTON5_RELEASED;
    env["BUTTON5_CLICKED"] = BUTTON5_CLICKED;
    env["BUTTON5_DOUBLE_CLICKED"] = BUTTON5_DOUBLE_CLICKED;
    env["BUTTON5_TRIPLE_CLICKED"] = BUTTON5_TRIPLE_CLICKED;
    #endif

    env["BUTTON_SHIFT"] = BUTTON_SHIFT;
    env["BUTTON_CTRL"] = BUTTON_CTRL;
    env["BUTTON_ALT"] = BUTTON_ALT;
    env["ALL_MOUSE_EVENTS"] = ALL_MOUSE_EVENTS;
    env["REPORT_MOUSE_POSITION"] = REPORT_MOUSE_POSITION;
}

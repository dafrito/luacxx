#include "../ncurses.hpp"
#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_attr.3x.html

int _COLOR_PAIR(lua_State* const state)
{
    lua::push(state, COLOR_PAIR(lua::get<int>(state, 1)));
    return 1;
}

int _PAIR_NUMBER(lua_State* const state)
{
    return 0;
}

void lua::ncurses_curs_attr(lua_State* const state)
{
    lua::thread env(state);

    env["attroff"] = attroff;
    env["wattroff"] = wattroff;
    env["attron"] = attron;
    env["wattron"] = wattron;
    env["attrset"] = attrset;
    env["wattrset"] = wattrset;

    env["color_set"] = color_set;
    env["wcolor_set"] = wcolor_set;

    env["standend"] = standend;
    env["wstandend"] = wstandend;
    env["standout"] = standout;
    env["wstandout"] = wstandout;

    env["attr_get"] = std::function<int(chtype*, short*, void*)>(attr_get);
    env["wattr_get"] = std::function<int(WINDOW*, chtype*, short*, void*)>(wattr_get);
    env["attr_off"] = std::function<int(chtype, void*)>(attr_off);
    env["wattr_off"] = std::function<int(WINDOW*, chtype, void*)>(wattr_off);
    env["attr_on"] = std::function<int(chtype, void*)>(attr_on);
    env["wattr_on"] = std::function<int(WINDOW*, chtype, void*)>(wattr_on);
    env["attr_set"] = std::function<int(chtype, short, void*)>(attr_set);
    env["wattr_set"] = std::function<int(WINDOW*, chtype, short, void*)>(wattr_set);

    env["chgat"] = std::function<int(int, chtype, short, const void *)>(chgat);
    env["wchgat"] = std::function<int(WINDOW*, int, chtype, short, const void *)>(wchgat);
    env["mvchgat"] = std::function<int(int, int, int, chtype, short, const void *)>(mvchgat);
    env["mvwchgat"] = std::function<int(WINDOW *, int, int, int, chtype, short, const void *)>(mvwchgat);

    env["COLOR_PAIR"] = _COLOR_PAIR;
    env["PAIR_NUMBER"] = _PAIR_NUMBER;

    env["A_NORMAL"] = A_NORMAL;
    env["A_STANDOUT"] = A_STANDOUT;
    env["A_UNDERLINE"] = A_UNDERLINE;
    env["A_REVERSE"] = A_REVERSE;
    env["A_BLINK"] = A_BLINK;
    env["A_DIM"] = A_DIM;
    env["A_BOLD"] = A_BOLD;
    env["A_PROTECT"] = A_PROTECT;
    env["A_INVIS"] = A_INVIS;
    env["A_ALTCHARSET"] = A_ALTCHARSET;
    //env["A_ITALIC"] = A_ITALIC;
    env["A_CHARTEXT"] = A_CHARTEXT;

    env["WA_HORIZONTAL"] = WA_HORIZONTAL;
    env["WA_LEFT"] = WA_LEFT;
    env["WA_LOW"] = WA_LOW;
    env["WA_RIGHT"] = WA_RIGHT;
    env["WA_TOP"] = WA_TOP;
    env["WA_VERTICAL"] = WA_VERTICAL;
}

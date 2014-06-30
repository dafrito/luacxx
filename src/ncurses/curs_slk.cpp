#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_slk.3x.html

void lua::ncurses_curs_slk(lua_State* const state)
{
    lua::thread env(state);

    env["slk_init"] = slk_init;
    env["slk_set"] = slk_set;
    env["slk_refresh"] = slk_refresh;
    env["slk_noutrefresh"] = slk_noutrefresh;
    env["slk_label"] = slk_label;
    env["slk_clear"] = slk_clear;
    env["slk_restore"] = slk_restore;
    env["slk_touch"] = slk_touch;
    env["slk_attron"] = std::function<int(const chtype)>(slk_attron);
    env["slk_attroff"] = std::function<int(const chtype)>(slk_attroff);
    env["slk_attrset"] = std::function<int(const chtype)>(slk_attrset);
    env["slk_attr_on"] = std::function<int(attr_t, void*)>(slk_attr_on);
    env["slk_attr_off"] = std::function<int(const attr_t, void*)>(slk_attr_off);
    env["slk_attr_set"] = std::function<int(const attr_t, short, void*)>(slk_attr_set);
    env["slk_attr"] = std::function<attr_t(void)>(slk_attr);
    env["slk_color"] = slk_color;
    env["slk_wset"] = slk_wset;
}

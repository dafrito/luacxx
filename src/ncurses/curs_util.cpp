#include "../ncurses.hpp"

#include "../luacxx/thread.hpp"

// http://invisible-island.net/ncurses/man/curs_util.3x.html

void lua::ncurses_curs_util(lua_State* const state)
{
    lua::thread env(state);

    env["unctrl"] = std::function<char*(chtype)>(unctrl);
    env["wunctrl"] = std::function<wchar_t*(cchar_t*)>(wunctrl);
    env["keyname"] = keyname;
    env["key_name"] = std::function<char*(wchar_t)>(key_name);
    env["filter"] = filter;
    env["nofilter"] = nofilter;
    env["use_env"] = use_env;
    env["use_tioctl"] = use_tioctl;
    env["putwin"] = putwin;
    env["getwin"] = getwin;
    env["delay_output"] = delay_output;
    env["flushinp"] = flushinp;
}

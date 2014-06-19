#include "ncurses.hpp"
#include "thread.hpp"
#include <cstring>

int ncurses_MEVENT_index(lua_State* const state)
{
    auto self = lua::get<MEVENT*>(state, 1);
    auto name = lua::get<const char*>(state, 2);
    if (!strcmp(name, "x")) {
        lua::push(state, self->x);
        return 1;
    }
    if (!strcmp(name, "y")) {
        lua::push(state, self->y);
        return 1;
    }
    if (!strcmp(name, "bstate")) {
        lua::push(state, self->bstate);
        return 1;
    }
    if (!strcmp(name, "z")) {
        lua::push(state, self->z);
        return 1;
    }
    if (!strcmp(name, "id")) {
        lua::push(state, self->id);
        return 1;
    }
    return 0;
}

namespace lua {

void ncurses_MEVENT_metatable(const lua::index& mt)
{
    mt["__index"] = ncurses_MEVENT_index;
}

void ncurses_chtype_metatable(const lua::index& mt)
{
    mt["__index"] = lua::push(mt.state(), lua::global(mt.state(), "bit32"));
}

} // namespace lua

int luaopen_luacxx_ncurses(lua_State* const state)
{
    lua::thread env(state);

    env["ERR"] = ERR;
    env["OK"] = OK;
    env["FALSE"] = FALSE;
    env["TRUE"] = TRUE;

    env["mmask_t"] = lua::value::table;
    env["mmask_t"]["new"] = lua::make_malloc<mmask_t>;

    env["attr_t"] = lua::value::table;
    env["attr_t"]["new"] = lua::make_malloc<attr_t>;

    env["chtype"] = lua::value::table;
    env["chtype"]["new"] = lua::make_malloc<chtype>;

    lua::ncurses_curs_add_wch(state);
    lua::ncurses_curs_add_wchstr(state);
    lua::ncurses_curs_addch(state);
    lua::ncurses_curs_addchstr(state);
    lua::ncurses_curs_addstr(state);
    lua::ncurses_curs_addwstr(state);
    lua::ncurses_curs_attr(state);
    lua::ncurses_curs_beep(state);
    lua::ncurses_curs_bkgd(state);
    lua::ncurses_curs_bkgrnd(state);
    lua::ncurses_curs_border(state);
    lua::ncurses_curs_border_set(state);
    lua::ncurses_curs_clear(state);
    lua::ncurses_curs_color(state);
    lua::ncurses_curs_delch(state);
    lua::ncurses_curs_deleteln(state);
    lua::ncurses_curs_extend(state);
    lua::ncurses_curs_get_wch(state);
    lua::ncurses_curs_get_wstr(state);
    lua::ncurses_curs_getcchar(state);
    lua::ncurses_curs_getch(state);
    lua::ncurses_curs_getstr(state);
    lua::ncurses_curs_getyx(state);
    lua::ncurses_curs_in_wch(state);
    lua::ncurses_curs_in_wchstr(state);
    lua::ncurses_curs_inch(state);
    lua::ncurses_curs_inchstr(state);
    lua::ncurses_curs_initscr(state);
    lua::ncurses_curs_inopts(state);
    lua::ncurses_curs_ins_wch(state);
    lua::ncurses_curs_ins_wstr(state);
    lua::ncurses_curs_insch(state);
    lua::ncurses_curs_insstr(state);
    lua::ncurses_curs_instr(state);
    lua::ncurses_curs_inwstr(state);
    lua::ncurses_curs_kernel(state);
    lua::ncurses_curs_legacy(state);
    lua::ncurses_curs_mouse(state);
    lua::ncurses_curs_move(state);
    lua::ncurses_curs_outopts(state);
    lua::ncurses_curs_overlay(state);
    lua::ncurses_curs_pad(state);
    lua::ncurses_curs_print(state);
    lua::ncurses_curs_printw(state);
    lua::ncurses_curs_refresh(state);
    lua::ncurses_curs_scanw(state);
    lua::ncurses_curs_scr_dump(state);
    lua::ncurses_curs_scroll(state);
    lua::ncurses_curs_slk(state);
    lua::ncurses_curs_termattrs(state);
    lua::ncurses_curs_touch(state);
    lua::ncurses_curs_util(state);
    lua::ncurses_curs_variables(state);
    lua::ncurses_curs_window(state);
    lua::ncurses_default_colors(state);
    lua::ncurses_define_key(state);
    lua::ncurses_key_defined(state);
    lua::ncurses_keybound(state);
    lua::ncurses_keyok(state);
    lua::ncurses_legacy_coding(state);
    lua::ncurses_resizeterm(state);
    lua::ncurses_wresize(state);

    return 0;
}

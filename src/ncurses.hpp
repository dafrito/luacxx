#ifndef LUACXX_NCURSES_INCLUDED
#define LUACXX_NCURSES_INCLUDED

#include "luacxx/stack.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/type/numeric.hpp"
#include "luacxx/type/function.hpp"
#include "luacxx/type/standard.hpp"

#include <ncurses.h>
#include <cstdio>

/*

=head1 NAME

ncurses 5.9

=head1 SYNOPSIS

    require "rainback.ncurses";

=head1 DESCRIPTION

This binding allows direct use of the ncurses terminal package, as described in:

    http://invisible-island.net/ncurses/man/ncurses.3x.html

=head1 LICENSE

ncurses itself is licensed under the following terms:

     ****************************************************************************
     * Copyright (c) 1998-2011,2012 Free Software Foundation, Inc.              *
     *                                                                          *
     * Permission is hereby granted, free of charge, to any person obtaining a  *
     * copy of this software and associated documentation files (the            *
     * "Software"), to deal in the Software without restriction, including      *
     * without limitation the rights to use, copy, modify, merge, publish,      *
     * distribute, distribute with modifications, sublicense, and/or sell       *
     * copies of the Software, and to permit persons to whom the Software is    *
     * furnished to do so, subject to the following conditions:                 *
     *                                                                          *
     * The above copyright notice and this permission notice shall be included  *
     * in all copies or substantial portions of the Software.                   *
     *                                                                          *
     * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
     * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
     * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
     * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
     * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
     * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
     * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
     *                                                                          *
     * Except as contained in this notice, the name(s) of the above copyright   *
     * holders shall not be used in advertising or otherwise to promote the     *
     * sale, use or other dealings in this Software without prior written       *
     * authorization.                                                           *
     ****************************************************************************

     ****************************************************************************
     *  Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995               *
     *     and: Eric S. Raymond <esr@snark.thyrsus.com>                         *
     *     and: Thomas E. Dickey                        1996-on                 *
     ****************************************************************************

As much as is possible, this binding uses the same license as ncurses itself.

*/

namespace lua {

void ncurses_MEVENT_metatable(const lua::index& mt);

template <>
struct Metatable<MEVENT>
{
    static constexpr const char* name = "MEVENT";

    static bool metatable(const lua::index& mt, MEVENT* const)
    {
        lua::ncurses_MEVENT_metatable(mt);
        return true;
    }
};

void ncurses_curs_add_wch(lua_State* const state);
void ncurses_curs_add_wchstr(lua_State* const state);
void ncurses_curs_addch(lua_State* const state);
void ncurses_curs_addchstr(lua_State* const state);
void ncurses_curs_addstr(lua_State* const state);
void ncurses_curs_addwstr(lua_State* const state);
void ncurses_curs_attr(lua_State* const state);
void ncurses_curs_beep(lua_State* const state);
void ncurses_curs_bkgd(lua_State* const state);
void ncurses_curs_bkgrnd(lua_State* const state);
void ncurses_curs_border(lua_State* const state);
void ncurses_curs_border_set(lua_State* const state);
void ncurses_curs_clear(lua_State* const state);
void ncurses_curs_color(lua_State* const state);
void ncurses_curs_delch(lua_State* const state);
void ncurses_curs_deleteln(lua_State* const state);
void ncurses_curs_extend(lua_State* const state);
void ncurses_curs_get_wch(lua_State* const state);
void ncurses_curs_get_wstr(lua_State* const state);
void ncurses_curs_getcchar(lua_State* const state);
void ncurses_curs_getch(lua_State* const state);
void ncurses_curs_getstr(lua_State* const state);
void ncurses_curs_getyx(lua_State* const state);
void ncurses_curs_in_wch(lua_State* const state);
void ncurses_curs_in_wchstr(lua_State* const state);
void ncurses_curs_inch(lua_State* const state);
void ncurses_curs_inchstr(lua_State* const state);
void ncurses_curs_initscr(lua_State* const state);
void ncurses_curs_inopts(lua_State* const state);
void ncurses_curs_ins_wch(lua_State* const state);
void ncurses_curs_ins_wstr(lua_State* const state);
void ncurses_curs_insch(lua_State* const state);
void ncurses_curs_insstr(lua_State* const state);
void ncurses_curs_instr(lua_State* const state);
void ncurses_curs_inwstr(lua_State* const state);
void ncurses_curs_kernel(lua_State* const state);
void ncurses_curs_legacy(lua_State* const state);
void ncurses_curs_mouse(lua_State* const state);
void ncurses_curs_move(lua_State* const state);
void ncurses_curs_outopts(lua_State* const state);
void ncurses_curs_overlay(lua_State* const state);
void ncurses_curs_pad(lua_State* const state);
void ncurses_curs_print(lua_State* const state);
void ncurses_curs_printw(lua_State* const state);
void ncurses_curs_refresh(lua_State* const state);
void ncurses_curs_scanw(lua_State* const state);
void ncurses_curs_scr_dump(lua_State* const state);
void ncurses_curs_scroll(lua_State* const state);
void ncurses_curs_slk(lua_State* const state);
void ncurses_curs_termattrs(lua_State* const state);
void ncurses_curs_touch(lua_State* const state);
void ncurses_curs_util(lua_State* const state);
void ncurses_curs_variables(lua_State* const state);
void ncurses_curs_window(lua_State* const state);
void ncurses_default_colors(lua_State* const state);
void ncurses_define_key(lua_State* const state);
void ncurses_key_defined(lua_State* const state);
void ncurses_keybound(lua_State* const state);
void ncurses_keyok(lua_State* const state);
void ncurses_legacy_coding(lua_State* const state);
void ncurses_resizeterm(lua_State* const state);
void ncurses_wresize(lua_State* const state);

}; // namespace lua

extern "C" int luaopen_luacxx_ncurses(lua_State* const);

#endif // LUACXX_NCURSES_INCLUDED

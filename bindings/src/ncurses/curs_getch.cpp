#include "../ncurses.hpp"
#include "../thread.hpp"

/*

=head1 NAME

curs_getch - http://invisible-island.net/ncurses/man/curs_getch.3x.html

=head1 SYNOPSIS

    require "luacxx.ncurses";

    initscr();

    local str = "Ain't got no time!!!";
    for i=1, #str do
        addch(string.byte(str, i));
        refresh();
    end;

    getch();
    endwin();

*/

int _KEY_F(lua_State* const state)
{
    lua::push(state, KEY_F(lua::get<int>(state, 1)));
    return 1;
}

void lua::ncurses_curs_getch(lua_State* const state)
{
    lua::thread env(state);

    env["getch"] = getch;
    env["wgetch"] = wgetch;
    env["mvgetch"] = mvgetch;
    env["mvwgetch"] = mvwgetch;
    env["ungetch"] = ungetch;
    env["has_key"] = has_key;

    env["KEY_BREAK"] = KEY_BREAK;
    env["KEY_DOWN"] = KEY_DOWN;
    env["KEY_UP"] = KEY_UP;
    env["KEY_LEFT"] = KEY_LEFT;
    env["KEY_RIGHT"] = KEY_RIGHT;
    env["KEY_HOME"] = KEY_HOME;
    env["KEY_BACKSPACE"] = KEY_BACKSPACE;

    env["KEY_F"] = _KEY_F;

    env["KEY_DL"] = KEY_DL;
    env["KEY_IL"] = KEY_IL;
    env["KEY_DC"] = KEY_DC;
    env["KEY_IC"] = KEY_IC;
    env["KEY_EIC"] = KEY_EIC;
    env["KEY_CLEAR"] = KEY_CLEAR;
    env["KEY_EOS"] = KEY_EOS;
    env["KEY_EOL"] = KEY_EOL;
    env["KEY_SF"] = KEY_SF;
    env["KEY_SR"] = KEY_SR;
    env["KEY_NPAGE"] = KEY_NPAGE;
    env["KEY_PPAGE"] = KEY_PPAGE;
    env["KEY_STAB"] = KEY_STAB;
    env["KEY_CTAB"] = KEY_CTAB;
    env["KEY_CATAB"] = KEY_CATAB;
    env["KEY_ENTER"] = KEY_ENTER;
    env["KEY_SRESET"] = KEY_SRESET;
    env["KEY_RESET"] = KEY_RESET;
    env["KEY_PRINT"] = KEY_PRINT;
    env["KEY_LL"] = KEY_LL;
    env["KEY_A1"] = KEY_A1;
    env["KEY_A3"] = KEY_A3;
    env["KEY_B2"] = KEY_B2;
    env["KEY_C1"] = KEY_C1;
    env["KEY_C3"] = KEY_C3;
    env["KEY_BTAB"] = KEY_BTAB;
    env["KEY_BEG"] = KEY_BEG;
    env["KEY_CANCEL"] = KEY_CANCEL;
    env["KEY_CLOSE"] = KEY_CLOSE;
    env["KEY_COMMAND"] = KEY_COMMAND;
    env["KEY_COPY"] = KEY_COPY;
    env["KEY_CREATE"] = KEY_CREATE;
    env["KEY_END"] = KEY_END;
    env["KEY_EXIT"] = KEY_EXIT;
    env["KEY_FIND"] = KEY_FIND;
    env["KEY_HELP"] = KEY_HELP;
    env["KEY_MARK"] = KEY_MARK;
    env["KEY_MESSAGE"] = KEY_MESSAGE;
    env["KEY_MOUSE"] = KEY_MOUSE;
    env["KEY_MOVE"] = KEY_MOVE;

    env["KEY_NEXT"] = KEY_NEXT;
    env["KEY_OPEN"] = KEY_OPEN;
    env["KEY_OPTIONS"] = KEY_OPTIONS;
    env["KEY_PREVIOUS"] = KEY_PREVIOUS;
    env["KEY_REDO"] = KEY_REDO;
    env["KEY_REFERENCE"] = KEY_REFERENCE;
    env["KEY_REFRESH"] = KEY_REFRESH;
    env["KEY_REPLACE"] = KEY_REPLACE;
    env["KEY_RESIZE"] = KEY_RESIZE;
    env["KEY_RESTART"] = KEY_RESTART;
    env["KEY_RESUME"] = KEY_RESUME;
    env["KEY_SAVE"] = KEY_SAVE;
    env["KEY_SBEG"] = KEY_SBEG;
    env["KEY_SCANCEL"] = KEY_SCANCEL;
    env["KEY_SCOMMAND"] = KEY_SCOMMAND;
    env["KEY_SCOPY"] = KEY_SCOPY;
    env["KEY_SCREATE"] = KEY_SCREATE;
    env["KEY_SDC"] = KEY_SDC;
    env["KEY_SDL"] = KEY_SDL;
    env["KEY_SELECT"] = KEY_SELECT;
    env["KEY_SEND"] = KEY_SEND;
    env["KEY_SEOL"] = KEY_SEOL;
    env["KEY_SEXIT"] = KEY_SEXIT;
    env["KEY_SFIND"] = KEY_SFIND;
    env["KEY_SHELP"] = KEY_SHELP;
    env["KEY_SHOME"] = KEY_SHOME;
    env["KEY_SIC"] = KEY_SIC;
    env["KEY_SLEFT"] = KEY_SLEFT;
    env["KEY_SMESSAGE"] = KEY_SMESSAGE;
    env["KEY_SMOVE"] = KEY_SMOVE;
    env["KEY_SNEXT"] = KEY_SNEXT;
    env["KEY_SOPTIONS"] = KEY_SOPTIONS;
    env["KEY_SPREVIOUS"] = KEY_SPREVIOUS;
    env["KEY_SPRINT"] = KEY_SPRINT;
    env["KEY_SREDO"] = KEY_SREDO;
    env["KEY_SREPLACE"] = KEY_SREPLACE;
    env["KEY_SRIGHT"] = KEY_SRIGHT;
    env["KEY_SRSUME"] = KEY_SRSUME;
    env["KEY_SSAVE"] = KEY_SSAVE;
    env["KEY_SSUSPEND"] = KEY_SSUSPEND;
    env["KEY_SUNDO"] = KEY_SUNDO;
    env["KEY_SUSPEND"] = KEY_SUSPEND;
    env["KEY_UNDO"] = KEY_UNDO;
}

acme = acme or {};

function acme.ncurses_getch()
    require "ncurses";

    initscr();

    local str = "Ain't got no time!!!";
    for i=1, #str do
        addch(string.byte(str, i));
        refresh();
    end;

    getch();
    endwin();
end;


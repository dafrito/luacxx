#include <vector>
#include <cmath>
#include <string>
#include <ncurses.h>
#include <iostream>
#include <stdexcept>

#include "menu.hpp"

using std::string;
using std::vector;

void die(const string& msg);

void make_menu()
{
	initscr();

	vector<string> options;
	options.push_back("Read the News");
	options.push_back("Fill the Bucket");
	options.push_back("Save the Options");
	options.push_back("Exit");

	mvaddstr(0, 0, "Main Menu");

	for (unsigned int i = 0; i < options.size(); i++) {
		mvprintw(4+(i*2), 10, "%d. %s", i+1, options[i].c_str());
	}

	mvprintw(4+(options.size()*2)+1, 10, "Use arrow keys to move; Enter to select:");

	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();

	int selection = 0;
	while(true) {
		int ch = getch();
		mvchgat(4+(selection*2), 10+3, options[selection].length(), 0, 0, NULL);
		switch(ch) {
			case KEY_DOWN:
				selection++;
				break;
			case KEY_UP:
				selection--;
				break;
			case '\n':
			case KEY_ENTER:
				if (options[selection] == "Exit") {
					endwin();
					exit(0);
				}
				break;
		}
		selection=std::min(std::max(selection, 0), (int)(options.size()-1));
		mvchgat(4+(selection*2), 10+3, options[selection].length(), A_REVERSE, 0, NULL);
	}

	endwin();
}

void die(const string& v)
{
	endwin();
	std::cerr << v << std::endl;
	exit(1);
}

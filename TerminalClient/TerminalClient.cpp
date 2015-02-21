/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  TerminalClient.cpp
 *
 *
 */

#include "TerminalClient.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
//#include <ncurses.h>
#include <curses.h>
#include <term.h>
#include <error.h>
#endif

static char termbuf[2048];
char buf2[30];

TerminalClient::TerminalClient() {
	// TODO Auto-generated constructor stub

	int wid = 20;
	int hei = 20;
#ifdef __linux__
	//initscr();
	//start_color();
	char *termtype = getenv("TERM");

	if (tgetent(termbuf, termtype) < 0) {
		error(EXIT_FAILURE, 0, "Could not access the termcap data base.\n");
	}
	hei = tgetnum("li");
	wid = tgetnum("co");
	//getmaxyx(stdscr, hei, wid);
#endif
	_drawer = new Drawer(wid, hei, BLACK);
}

TerminalClient::~TerminalClient() {
	delete _drawer;
#ifdef __linux__
	//endwin();
#endif
}

inline std::string ColorToCharSeq(Color fg, Color bg){
	std::string start = "\033[";

	if(fg == BLACK) start += "30;";
	else if(fg == RED) start += "31;";
	else if(fg == GREEN) start += "32;";
	else if(fg == BROWN) start += "33;";
	else if(fg == BLUE) start += "34;";
	else if(fg == MAGENTA) start += "35;";
	else if(fg == CYAN) start += "36;";
	else if(fg == GRAY) start += "37;";
	else if(fg == DARKGRAY) start += "90;";
	else if(fg == LIGHTRED) start += "91;";
	else if(fg == LIGHTGREEN) start += "92;";
	else if(fg == YELLOW) start += "93;";
	else if(fg == LIGHTBLUE) start += "94;";
	else if(fg == LIGHTMAGENTA) start += "95;";
	else if(fg == LIGHTCYAN) start += "96;";
	else start += "97;";

	if(bg == BLACK) start += "40m";
	else if(bg == RED) start += "41m";
	else if(bg == GREEN) start += "42m";
	else if(bg == BROWN) start += "43m";
	else if(bg == BLUE) start += "44m";
	else if(bg == MAGENTA) start += "45m";
	else if(bg == CYAN) start += "46m";
	else if(bg == GRAY) start += "47m";
	else if(bg == DARKGRAY) start += "100m";
	else if(bg == LIGHTRED) start += "101m";
	else if(bg == LIGHTGREEN) start += "102m";
	else if(bg == YELLOW) start += "103m";
	else if(bg == LIGHTBLUE) start += "104m";
	else if(bg == LIGHTMAGENTA) start += "105m";
	else if(bg == LIGHTCYAN) start += "106m";
	else start += "107m";

	return start;
}

void TerminalClient::paint()
{
#ifdef __linux__
	puts(tgetstr("cl", ((char**)&buf2)));
#endif
	Color oldFG=BROWN, oldBG=BLACK;
	for(int y=0; y<_drawer->getHeight(); y++){
		for(int x=0; x<_drawer->getWidth(); x++){
			Color bg = BLACK;
			for(int i=0; i<_drawer->_L.size(); i++){
				char cell = _drawer->_L[i]->getCell(x,y);
				if(cell == 0)
					continue;
				if(cell == ' ')
					bg = _drawer->_L[i]->getColor();
				Color fg = _drawer->_L[i]->getColor();
				if(fg != oldFG || bg != oldBG){
					oldFG = fg;
					oldBG = bg;
					printf("%s", ColorToCharSeq(_drawer->_L[i]->getColor(), bg).c_str());
				}
				printf("\033[%d;%df", y+1, x+1);
				printf("%c", cell);
			}
		}
	}
	fflush(stdout);

#ifdef __linux__
	//refresh();
#endif
}


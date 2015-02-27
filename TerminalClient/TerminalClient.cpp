/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  TerminalClient.cpp
 *
 *
 */

#include "TerminalClient.h"

#ifdef __linux__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ncurses.h>
#include <term.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <poll.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <algorithm>

static char termbuf[2048];
static char buf2[30];
static struct termios oldterm, curterm;
static bool contin = true;

static void handleSignal(int signo){
	tcsetattr(0, TCSANOW, &oldterm);
	contin = false;
	rl_callback_handler_remove();
}


TerminalClient::TerminalClient() {
	int wid = 20;
	int hei = 20;

	// Save console state, and set up signals
	tcgetattr(0, &oldterm);
	struct sigaction signalHndlr;
	memset(&signalHndlr, 0, sizeof(struct sigaction));
	signalHndlr.sa_handler = handleSignal;
	sigaction(SIGINT, &signalHndlr, NULL);
	sigaction(SIGQUIT, &signalHndlr, NULL);
	sigaction(SIGTERM, &signalHndlr, NULL);
	memset(&signalHndlr, 0, sizeof(struct sigaction));
	signalHndlr.sa_handler = SIG_IGN;
	sigaction(SIGTTOU, &signalHndlr, NULL);

	char *termtype = getenv("TERM");

	if (tgetent(termbuf, termtype) < 0) {
		error(EXIT_FAILURE, 0, "Could not access the termcap data base.\n");
	}
	hei = tgetnum("li")-1; // last line for input box
	wid = tgetnum("co");
	_drawer = new Drawer(wid, hei, BLACK);
	_supportBrightColors = false;
}

TerminalClient::~TerminalClient() {
	rl_callback_handler_remove();
	handleSignal(0);
	delete _drawer;
}

void TerminalClient::promptForColorSupport(){
	_supportBrightColors = true;
	_drawer->resetScreen(BLACK);
	_drawer->printFormattedTextWW(_drawer->newLayer(GRAY),
			"Is The Text Below *Yellow* ? [It Says: I Support Colors]\n\n"
			"<D>I Support Colors\n\n\n"
			"<7>Enter yes or y if you do, otherwise any key.\n");
	std::string in = inputGetLine();
	_supportBrightColors = false;
	std::transform(in.begin(), in.end(), in.begin(), ::tolower);
	if(in == "y" || in == "yes"){
		_supportBrightColors = true;
	}
}

void TerminalClient::setSupportBrightColors(bool b){
	_supportBrightColors = b;
}

std::string TerminalClient::ColorToCharSeq(Color fg, Color bg){
	std::string start = "\033[";

	if(fg == BLACK) start += "0;30;";
	else if(fg == RED) start += "0;31;";
	else if(fg == GREEN) start += "0;32;";
	else if(fg == BROWN) start += "0;33;";
	else if(fg == BLUE) start += "0;34;";
	else if(fg == MAGENTA) start += "0;35;";
	else if(fg == CYAN) start += "0;36;";
	else if(fg == GRAY) start += "0;37;";
	else{
		if(_supportBrightColors){
			if(fg == DARKGRAY) start += "0;90;";
			else if(fg == LIGHTRED) start += "0;91;";
			else if(fg == LIGHTGREEN) start += "0;92;";
			else if(fg == YELLOW) start += "0;93;";
			else if(fg == LIGHTBLUE) start += "0;94;";
			else if(fg == LIGHTMAGENTA) start += "0;95;";
			else if(fg == LIGHTCYAN) start += "0;96;";
			else start += "0;97;";
		}else{
			if(fg == DARKGRAY) start += "1;30;";
				else if(fg == LIGHTRED) start += "1;31;";
				else if(fg == LIGHTGREEN) start += "1;32;";
				else if(fg == YELLOW) start += "1;33;";
				else if(fg == LIGHTBLUE) start += "1;34;";
				else if(fg == LIGHTMAGENTA) start += "1;35;";
				else if(fg == LIGHTCYAN) start += "1;36;";
				else start += "1;37;";
		}
	}

	if(bg == BLACK) start += "40m";
	else if(bg == RED) start += "41m";
	else if(bg == GREEN) start += "42m";
	else if(bg == BROWN) start += "43m";
	else if(bg == BLUE) start += "44m";
	else if(bg == MAGENTA) start += "45m";
	else if(bg == CYAN) start += "46m";
	else if(bg == GRAY) start += "47m";
	else{
		if(_supportBrightColors){
			if(bg == DARKGRAY) start += "100m";
			else if(bg == LIGHTRED) start += "101m";
			else if(bg == LIGHTGREEN) start += "102m";
			else if(bg == YELLOW) start += "103m";
			else if(bg == LIGHTBLUE) start += "104m";
			else if(bg == LIGHTMAGENTA) start += "105m";
			else if(bg == LIGHTCYAN) start += "106m";
			else start += "107m";
		}else{
			if(bg == DARKGRAY) start += "40m";
			else if(bg == LIGHTRED) start += "41m";
			else if(bg == LIGHTGREEN) start += "42m";
			else if(bg == YELLOW) start += "43m";
			else if(bg == LIGHTBLUE) start += "44m";
			else if(bg == LIGHTMAGENTA) start += "45m";
			else if(bg == LIGHTCYAN) start += "46m";
			else start += "47m";
		}
	}

	return start;
}

void TerminalClient::paint()
{
	if(!_drawer->needsPaint())
		return;

	//if(_im == IM_ASYNC_LINE && ::rl_refresh_line())

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
	// command bar
	/*printf("\033[%d;%df", _drawer->getHeight()+1, 1);
	printf("%s", ColorToCharSeq(WHITE, BLACK).c_str());
	for(int i=0; i<_drawer->getWidth(); i++)
		printf(" ");*/
	fflush(stdout);
	rl_forced_update_display();
}

void TerminalClient::disableInput(){
	AbstractClient::disableInput();
	tcgetattr(0, &curterm);
	curterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &curterm);
}

void TerminalClient::enableKeyInput(void (*callback)(void*,char), void *obj){
	AbstractClient::enableKeyInput(callback, obj);
	tcgetattr(0, &curterm);
	curterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &curterm);
}

std::string TerminalClient::inputGetLine(){
	paint();

	printf("\033[%d;%df", _drawer->getHeight()+1, 1);
	printf("%s", ColorToCharSeq(GRAY, BLACK).c_str());
	fflush(stdout);

	static struct termios preLine, tmp;
	tcgetattr(0, &preLine);
	tcgetattr(0, &tmp);

	tmp.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tmp);

	char *s = readline(" > ");
	add_history(s);
	std::string ret = std::string(s);
	free(s);

	tcsetattr(0, TCSANOW, &preLine);
	_drawer->onLayerModified();
	paint();
	return ret;
}

bool TerminalClient::processInput(){
	// poll for input
	struct pollfd pfds[1];
	pfds[0].fd = 0;
	pfds[0].events = POLLIN;
	int sz = poll(pfds, 1, 0);

	if(_im == IM_ASYNC_LINE){
		if(sz > 0){
			rl_callback_read_char();
		}
	}else{
		// consume input & propogate it to where it is requested
		if (sz > 0) {
			char c;
			read(0, &c, 1);
			if(_im == IM_KEY_ACCEPT){
				_keyInCallback(_keyInCallbackObj, c);
			}
		}
	}
	return contin && !_quit;
}

static TerminalClient *termSelf;
void TerminalClient::lineHandler(char *line){
	if(line == NULL){ // escape
		rl_callback_handler_remove();
		contin = false;
		return;
	}
	add_history(line);
	std::string ret = std::string(line);
	free(line);

	rl_callback_handler_remove();

	rl_line_buffer[0] = 0;
	termSelf->disableInput();
	termSelf->_drawer->onLayerModified();
	termSelf->paint();

	// call callback
	(termSelf->_lineInCallback)(termSelf->_lineInCallbackObj, ret);
}

void TerminalClient::asyncInputGetLine(void (*callback)(void*, std::string), void *obj){
	if(_im == IM_ASYNC_LINE)
		return;

	paint();
	_im = IM_ASYNC_LINE;

	char buf[256];
	memset(buf, 0, 256*sizeof(char));
	sprintf(buf, "\033[%d;%df%s > ", _drawer->getHeight()+1, 1,ColorToCharSeq(GRAY, BLACK).c_str());

	static struct termios preLine;
	tcgetattr(0, &preLine);
	preLine.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &preLine);

	_lineInCallbackObj = obj;
	_lineInCallback = callback;

	termSelf = this;
	rl_callback_handler_install(buf, lineHandler);
}


#endif // __linux__



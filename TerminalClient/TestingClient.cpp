/*
 * TestingClient.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: jeffrey
 */

#include <TerminalClient/TestingClient.h>


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

static bool contin = true;

TestingClient::TestingClient() {
	// TODO Auto-generated constructor stub
	int hei = 23;
	int wid = 80;
	_drawer = new Drawer(wid, hei, BLACK);
}

TestingClient::~TestingClient() {
	// TODO Auto-generated destructor stub
}

bool TestingClient::processInput(){
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
				_ir->recvChar(c);
			}
		}
	}
	return contin && !_quit;
}

std::string TestingClient::inputGetLine(){
	char *s = readline(" > ");
	add_history(s);
	std::string ret = std::string(s);
	free(s);

	return ret;
}


static TestingClient *termSelf;
void TestingClient::lineHandler(char *line){
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

	// call callback
	termSelf->_ir->recvString(ret);
}

void TestingClient::asyncInputGetLine(InputReceiver *ir){
	if(_im == IM_ASYNC_LINE)
		return;

	paint();
	_im = IM_ASYNC_LINE;

	char buf[256];
	memset(buf, 0, 256*sizeof(char));
	sprintf(buf, " > ");

	_ir = ir;

	termSelf = this;
	rl_callback_handler_install(buf, lineHandler);
}



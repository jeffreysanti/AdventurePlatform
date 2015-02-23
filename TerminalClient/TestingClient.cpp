/*
 * TestingClient.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: jeffrey
 */

#include <TerminalClient/TestingClient.h>

TestingClient::TestingClient() {
	// TODO Auto-generated constructor stub
	int hei = 23;
	int wid = 80;
	_drawer = new Drawer(wid, hei, BLACK);
}

TestingClient::~TestingClient() {
	// TODO Auto-generated destructor stub
}


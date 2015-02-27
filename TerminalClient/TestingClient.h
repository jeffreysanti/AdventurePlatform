/*
 * TestingClient.h
 *
 *  Created on: Feb 22, 2015
 *      Author: jeffrey
 */

#ifndef TERMINALCLIENT_TESTINGCLIENT_H_
#define TERMINALCLIENT_TESTINGCLIENT_H_

#include <AbstractClient.h>

class TestingClient: public AbstractClient {
public:
	TestingClient();
	virtual ~TestingClient();

	virtual bool processInput();

	virtual std::string inputGetLine();

	static void lineHandler(char *line);
	virtual void asyncInputGetLine(InputReceiver *ir);
};

#endif /* TERMINALCLIENT_TESTINGCLIENT_H_ */

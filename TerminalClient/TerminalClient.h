/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  TerminalClient.h
 *
 *
 */

#ifndef TERMINALCLIENT_H_
#define TERMINALCLIENT_H_

#include <AbstractClient.h>

class TerminalClient: public AbstractClient {
public:
	TerminalClient();
	virtual ~TerminalClient();

	virtual void paint();
};

#endif /* TERMINALCLIENT_H_ */

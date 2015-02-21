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

#ifdef __linux__

class TerminalClient: public AbstractClient {

public:

	TerminalClient();
	virtual ~TerminalClient();

	virtual void paint();
	virtual bool processInput();

	virtual void disableInput();
	virtual void enableKeyInput(void (*callback)(void*,char), void *obj);
	virtual std::string inputGetLine();

private:



};

#endif //  __linux__

#endif /* TERMINALCLIENT_H_ */

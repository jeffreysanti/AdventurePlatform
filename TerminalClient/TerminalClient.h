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
	virtual void enableKeyInput(InputReceiver *ir);
	virtual std::string inputGetLine();

	std::string ColorToCharSeq(Color fg, Color bg);
	void setSupportBrightColors(bool b);
	void promptForColorSupport();

	virtual void asyncInputGetLine(InputReceiver *ir);

	static void lineHandler(char *line);

private:

	bool _supportBrightColors;


};

#endif //  __linux__

#endif /* TERMINALCLIENT_H_ */

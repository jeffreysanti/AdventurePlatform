/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  AbstractClient.h
 *  Interface for client
 *
 */

#ifndef ABSTRACTCLIENT_H_
#define ABSTRACTCLIENT_H_

#include "Drawer.h"
#include <memory>

enum InputMode{
	IM_NO_INPUT,
	IM_KEY_ACCEPT,
	IM_ASYNC_LINE
};

class InputReceiver{
public:
	virtual void recvChar(char c);
	virtual void recvString(std::string s);
};

class AbstractClient {
public:
	AbstractClient();
	virtual ~AbstractClient();

	virtual void paint();
	virtual bool processInput();

	virtual void disableInput();
	virtual void enableKeyInput(InputReceiver *ir);
	virtual std::string inputGetLine();

	virtual void asyncInputGetLine(InputReceiver *ir);

	void quit();

	Drawer *getDrawer();
protected:
	InputReceiver *_ir;
	Drawer * _drawer;
	InputMode _im;
	bool _quit;
};

#endif /* ABSTRACTCLIENT_H_ */

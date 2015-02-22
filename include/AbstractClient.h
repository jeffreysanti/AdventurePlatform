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

enum InputMode{
	IM_NO_INPUT,
	IM_KEY_ACCEPT,
	IM_ASYNC_LINE
};

class AbstractClient {
public:
	AbstractClient();
	virtual ~AbstractClient();

	virtual void paint();
	virtual bool processInput();

	virtual void disableInput();
	virtual void enableKeyInput(void (*callback)(void*, char), void *obj);
	virtual std::string inputGetLine();

	virtual void asyncInputGetLine(void (*callback)(void*, std::string), void *obj);


	Drawer *getDrawer();
protected:
	Drawer * _drawer;
	InputMode _im;

	void (*_keyInCallback)(void*, char);
	void *_keyInCallbackObj;

	void (*_lineInCallback)(void*, std::string);
	void *_lineInCallbackObj;
};

#endif /* ABSTRACTCLIENT_H_ */

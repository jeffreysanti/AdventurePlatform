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
	IM_KEY_ACCEPT
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


	Drawer *getDrawer();
protected:
	Drawer * _drawer;
	InputMode _im;

	void (*_keyInCallback)(void*, char);
	void *_keyInCallbackObj;
};

#endif /* ABSTRACTCLIENT_H_ */

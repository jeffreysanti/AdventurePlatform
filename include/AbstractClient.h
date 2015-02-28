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

enum DisplayMode{
	DM_PLAYER_NAV,
	DM_CUSTOM_HOLD,
	DM_CUSTOM_TIMED
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

	void updateTime(long long time);
	long long getTime();
	void setDisplayMode(DisplayMode dm, long long switchTime=0);
	DisplayMode getDisplayMode();
	void quit();
	Drawer *getDrawer();
protected:
	InputReceiver *_ir;
	Drawer * _drawer;
	InputMode _im;
	bool _quit;
	DisplayMode _dm;
	long long _dmSwitchTime;
	long long _time;
};

#endif /* ABSTRACTCLIENT_H_ */

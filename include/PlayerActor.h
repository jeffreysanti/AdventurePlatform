/*
 * PlayerActor.h
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#ifndef INCLUDE_PLAYERACTOR_H_
#define INCLUDE_PLAYERACTOR_H_

#include <Actor.h>
#include <AbstractClient.h>
#include <string>
#include "ItemManager.h"

class PlayerActor: public Actor, InputReceiver {
public:
	PlayerActor(Space *space, AbstractClient *cli, ItemManager *im);
	virtual ~PlayerActor();

	void onUpdate(long long tick);

	void showLocation();

	virtual void recvChar(char c);
	virtual void recvString(std::string s);

protected:

	AbstractClient *_cli;
	std::string _name;
	DisplayMode _oldDM;
	ItemManager *_IM;

};

#endif /* INCLUDE_PLAYERACTOR_H_ */

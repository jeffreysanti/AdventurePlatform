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

class PlayerActor: public Actor {
public:
	PlayerActor(Space *space, AbstractClient *cli);
	virtual ~PlayerActor();

	void onUpdate(long long tick);

	static void __keyboardHandler(void *self, std::string s);

protected:

	void keyboardHandler(std::string s);

	AbstractClient *_cli;
	std::string _name;

};

#endif /* INCLUDE_PLAYERACTOR_H_ */

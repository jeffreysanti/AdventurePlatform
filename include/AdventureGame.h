/*
 *  Jeffrey Santi
 *  Adventure Platform
 *
 *  AdventureGame.h
 *  Game Container
 *
 */

#ifndef ADVENTUREGAME_H_
#define ADVENTUREGAME_H_

#include <string>
#include "AbstractClient.h"
#include "ActorManager.h"
#include "SpaceManager.h"
#include "ItemManager.h"

enum RunType{
	RT_SERVER,
	RT_DUMB_CLIENT,
	RT_CLIENT
};

class AdventureGame {
public:
	AdventureGame(RunType rt);
	virtual ~AdventureGame();

	int mainLoop(AbstractClient *cli);

	static void __defaultKeyboardHandler(void *self, char c);
	void defaultKeyboardHandler(char c);

private:
	RunType _rt;
	bool _quit;
	long long _ticks;

	ActorManager _A;
	SpaceManager _S;
	ItemManager _I;
};

#endif /* ADVENTUREGAME_H_ */

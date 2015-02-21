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

private:
	RunType _rt;
};

#endif /* ADVENTUREGAME_H_ */

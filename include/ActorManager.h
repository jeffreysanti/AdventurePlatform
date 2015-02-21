/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  ActorManager.h
 *  Contains Game Actors
 *
 */

#ifndef ACTORMANAGER_H_
#define ACTORMANAGER_H_

#include <vector>
#include "Actor.h"

class ActorManager {
public:
	ActorManager();
	virtual ~ActorManager();

private:
	std::vector<Actor> A;
};

#endif /* ACTORMANAGER_H_ */

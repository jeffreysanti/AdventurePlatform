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
#include <map>
#include "Actor.h"

class ActorManager {
public:
	ActorManager();
	virtual ~ActorManager();

	void registerActor(std::string uuid, Actor *actor);
	void registerActor(Actor *actor);

	void onUpdate(long long tick);

private:
	std::vector<Actor*> _A;
	std::map<std::string, Actor*> _AU;
};

#endif /* ACTORMANAGER_H_ */

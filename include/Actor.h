/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  Actor.h
 *  In-World Movable Unit
 *
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include <string>
#include <vector>
#include "Space.h"

class ActorManager;

class Actor {

	friend class ActorManager;

public:
	Actor(Space *space);
	virtual ~Actor();

	std::string getClass();

	virtual void onUpdate(long long tick);

protected:

	std::string _class;
	std::string _uuid;
	bool _unique;
	Space *_space;

private:
	void setUniqueUUID(bool unique, std::string uuid);


};

#endif /* ACTOR_H_ */

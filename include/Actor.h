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

	void setSpace(Space *space);

	virtual void onUpdate(long long tick) = 0;

protected:

	std::string _class;
	Space *_space;

private:
	void setUniqueUUID(bool unique, std::string uuid);
	std::string _uuid;
	bool _unique;
};


#endif /* ACTOR_H_ */

/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  Actor.cpp
 *  In-World Movable Unit
 *
 */

#include <Actor.h>

Actor::Actor(Space *space) {
	// TODO Auto-generated constructor stub
	_space = space;
}

Actor::~Actor() {
	// TODO Auto-generated destructor stub
}

std::string Actor::getClass(){
	return _class;
}

void Actor::setUniqueUUID(bool unique, std::string uuid){
	_unique = unique;
	_uuid = uuid;
}

void Actor::onUpdate(long long tick){

}



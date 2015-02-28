/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  ActorManager.cpp
 *  Contains Game Actors
 *
 */

#include <ActorManager.h>
#include <assert.h>
#include <iostream>
#include <cstdlib>

ActorManager::ActorManager() {
	// TODO Auto-generated constructor stub

}

ActorManager::~ActorManager() {
	for(int i=0; i<_A.size(); i++){
		delete _A[i];
	}
	_A.clear();

	for(std::map<std::string, Actor*>::iterator it = _AU.begin(); it != _AU.end(); ++it){
		delete (*it).second;
	}
	_AU.clear();
}

void ActorManager::registerActor(std::string uuid, Actor *actor){
	if(uuid == ""){
		_A.push_back(actor);
		actor->setUniqueUUID(false, "");
	}else{
		if(_AU.find(uuid) != _AU.end()){
			std::cerr << "UNIQUE ACTOR REGISTERED AGAIN!";
			exit(1);
		}
		_AU[uuid] = actor;
		actor->setUniqueUUID(true, uuid);
	}
}
void ActorManager::registerActor(Actor *actor){
	registerActor("", actor);
}

void ActorManager::onUpdate(long long tick){
	for(int i=0; i<_A.size(); i++){
		_A[i]->onUpdate(tick);
	}
	for(std::map<std::string, Actor*>::iterator it = _AU.begin(); it != _AU.end(); ++it){
		(*it).second->onUpdate(tick);
	}
}


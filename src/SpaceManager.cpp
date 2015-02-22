/*
 * SpaceManager.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#include <SpaceManager.h>
#include <iostream>
#include <cstdlib>

SpaceManager::SpaceManager() {
	// TODO Auto-generated constructor stub

}

SpaceManager::~SpaceManager() {
	for(std::map<std::string, Space*>::iterator it = _S.begin(); it != _S.end(); ++it) {
		delete (*it).second;
	}
	_S.clear();
}

Space *SpaceManager::newSpace(std::string uuid){
	if(_S.find(uuid) != _S.end()){
		std::cerr << "UNIQUE Space REGISTERED AGAIN!";
		exit(1);
	}
	Space *space = new Space(uuid);
	_S[uuid] = space;
	return space;
}


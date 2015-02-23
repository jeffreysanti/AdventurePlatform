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

Gateway *SpaceManager::newGateway(std::string uuid, Space *src, Space *dest, std::string dir){
	if(_G.find(uuid) != _G.end()){
		std::cerr << "UNIQUE Gateway REGISTERED AGAIN!";
		exit(1);
	}
	Gateway *gw = new Gateway(uuid, src, dest, dir);
	src->addGatewayOut(gw);
	_G[uuid] = gw;
	return gw;
}

Space *SpaceManager::getSpace(std::string uuid){
	std::map<std::string, Space*>::iterator it = _S.find(uuid);
	if(it == _S.end()){
		std::cerr << "UNIQUE Space REGISTERED AGAIN!";
		exit(1);
	}
	return (*it).second;
}


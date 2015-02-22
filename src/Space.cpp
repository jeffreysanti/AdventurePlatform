/*
 * Space.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#include <Space.h>
#include <algorithm>
#include <Gateway.h>

Space::Space(std::string uuid) {
	_uuid = uuid;
}

Space::~Space() {

}

void Space::setName(std::string name){
	_name = name;
}

std::string Space::getName(){
	return _name;
}

std::string Space::getUUID(){
	return _uuid;
}

void Space::addGatewayOut(Gateway *gateway){
	_D.push_back(gateway);
	std::sort(_D.begin(), _D.end(), Gateway::compareGatewayStrings);
}




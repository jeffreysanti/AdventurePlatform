/*
 * Gateway.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#include <Gateway.h>
#include <Space.h>
#include <algorithm>

Gateway::Gateway(std::string uuid, Space *src, Space *dest, std::string primaryDirection) {
	_uuid = uuid;
	_src = src;
	_dest = dest;
	_primaryDirection = primaryDirection;
	_enabled = true;
}

Gateway::~Gateway() {
	_dirs.clear();
}

std::string Gateway::getUUID(){
	return _uuid;
}

Space *Gateway::getSource(){
	return _src;
}

Space *Gateway::getDestination(){
	return _dest;
}

std::string Gateway::getPrimaryDirection(){
	return _primaryDirection;
}

void Gateway::addDirectionString(std::string alt){
	std::transform(alt.begin(), alt.end(), alt.begin(), ::tolower);
	_dirs.insert(alt);
}

bool Gateway::testDirection(std::string input){
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	std::string testPrimary = _primaryDirection;
	std::transform(testPrimary.begin(), testPrimary.end(), testPrimary.begin(), ::tolower);

	if(testPrimary == input)
		return true;
	if(_dirs.find(input) != _dirs.end())
		return true;
	return false;
}

bool Gateway::isEnabled(){
	return _enabled;
}

void Gateway::setEnabled(bool enabled){
	_enabled = enabled;
}






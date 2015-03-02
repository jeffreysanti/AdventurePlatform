/*
 * Item.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: jeffrey
 */

#include <Item.h>
#include "Space.h"

Item::Item() {
	_unique = false;
	_space = NULL;
}

Item::~Item() {
	// TODO Auto-generated destructor stub
}

std::string Item::getClass(){
	return _class;
}

void Item::setUniqueUUID(bool unique, std::string uuid){
	_unique = unique;
	_uuid = uuid;
}

Space *Item::getSpace(){
	return _space;
}

void Item::setSpace(Space *space){
	_space = space;
}

std::string Item::getPrimaryName(){
	return _primaryName;
}

void Item::setPrimaryName(const std::string &name){
	_primaryName = name;
}

void Item::addNameString(std::string alt){
	std::transform(alt.begin(), alt.end(), alt.begin(), ::tolower);
	_names.insert(alt);
}

bool Item::testName(std::string input){
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	std::string testPrimary = _primaryName;
	std::transform(testPrimary.begin(), testPrimary.end(), testPrimary.begin(), ::tolower);

	if(testPrimary == input)
		return true;
	if(_names.find(input) != _names.end())
		return true;
	return false;
}

void Item::outputToDrawer(Drawer *draw, DrawLayer *layer){
	std::string sOutput = " * " + getPrimaryName();
	draw->printFormattedTextWW(layer, sOutput.c_str());
}

void Item::onUse(std::string vb, Actor *actor, AbstractClient *cli){
}



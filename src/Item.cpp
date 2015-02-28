/*
 * Item.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: jeffrey
 */

#include <Item.h>
#include "Space.h"


void ItemDisplayer::outputToDrawer(Drawer *draw, DrawLayer *layer){
	std::string sOutput = " * " + item->getPrimaryName();
	draw->printFormattedTextWW(layer, sOutput.c_str());
}
ItemDisplayer::~ItemDisplayer(){
}

void ItemUser::useItem(std::string vb, Actor *actor, AbstractClient *cli){
}
ItemUser::~ItemUser(){
}

Item::Item() {
	_unique = false;
	_space = NULL;
	_displayer = new ItemDisplayer();
	_displayer->item = this;
	_user = new ItemUser();
	_user->item = this;
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

void Item::setPrimaryName(std::string name){
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

void Item::setDisplayer(std::auto_ptr<ItemDisplayer> disp){
	if(_displayer != NULL)
		delete _displayer;
	_displayer = disp.get();
	disp.release();
	_displayer->item = this;
}

void Item::outputToDrawer(Drawer *draw, DrawLayer *layer){
	if(_displayer != NULL){
		_displayer->outputToDrawer(draw, layer);
	}
}

void Item::onUse(std::string vb, Actor *actor, AbstractClient *cli){
	if(_user != NULL){
		_user->useItem(vb, actor, cli);
	}
}
void Item::setUser(std::auto_ptr<ItemUser> user){
	if(_user != NULL)
		delete _user;
	_user = user.get();
	user.release();
	_user->item = this;
}


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
	_displayer = new GatewayDisplayer();
	_actorAttempter = new GatewayActorAttempter();
}

Gateway::~Gateway() {
	_dirs.clear();
	if(_displayer != NULL){
		delete _displayer;
	}if(_actorAttempter != NULL){
		delete _actorAttempter;
	}
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

bool Gateway::actorAttemptGateway(Actor *actor, AbstractClient *cli){
	if(_actorAttempter != NULL){
		return _actorAttempter->actorAttemptGateway(actor, cli);
	}
	return false;
}

bool Gateway::isEnabled(){
	return _enabled;
}

void Gateway::setEnabled(bool enabled){
	_enabled = enabled;
}

void Gateway::outputToDrawer(Drawer *draw, DrawLayer *layer){
	if(_displayer != NULL){
		_displayer->outputToDrawer(draw, layer);
	}
}

void Gateway::setDisplayer(std::auto_ptr<GatewayDisplayer> disp){
	if(_displayer != NULL)
		delete _displayer;
	_displayer = disp.get();
	disp.release();
	_displayer->gw = this;
}
void Gateway::setActorAttempter(std::auto_ptr<GatewayActorAttempter> attempt){
	if(_actorAttempter != NULL)
		delete _actorAttempter;
	_actorAttempter = attempt.get();
	attempt.release();
	_actorAttempter->gw = this;
}






void GatewayDisplayer::outputToDrawer(Drawer *draw, DrawLayer *layer){
	std::string sOutput = " * " + gw->getPrimaryDirection();
	draw->printFormattedTextWW(layer, sOutput.c_str());
}

GatewayDisplayer::~GatewayDisplayer(){

}

bool GatewayActorAttempter::actorAttemptGateway(Actor *actor, AbstractClient *cli){
	actor->setSpace(gw->getDestination());
	return true;
}

GatewayActorAttempter::~GatewayActorAttempter(){

}





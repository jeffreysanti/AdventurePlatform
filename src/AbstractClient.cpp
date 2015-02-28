/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  AbstractClient.cpp
 *  Interface for client
 *
 */

#include <AbstractClient.h>


void InputReceiver::recvChar(char c){

}
void InputReceiver::recvString(std::string s){

}

AbstractClient::AbstractClient() {
	_drawer = NULL;
	_im = IM_NO_INPUT;
	_quit = false;
	_ir = NULL;
	_dm = DM_PLAYER_NAV;
	_time = 0;
	_dmSwitchTime = 0;
}

AbstractClient::~AbstractClient() {
}

void AbstractClient::disableInput(){
	_im = IM_NO_INPUT;
}

void AbstractClient::enableKeyInput(InputReceiver *ir){
	_im = IM_KEY_ACCEPT;
	_ir = ir;
}

std::string AbstractClient::inputGetLine(){
	return "";
}

void AbstractClient::paint(){
}
bool AbstractClient::processInput(){
	return true;
}

Drawer *AbstractClient::getDrawer()
{
	return _drawer;
}

void AbstractClient::asyncInputGetLine(InputReceiver *ir){

}

void AbstractClient::updateTime(long long time){
	_time = time;
	if(_dm == DM_CUSTOM_TIMED && _time >= _dmSwitchTime){
		this->disableInput();
		_dm = DM_PLAYER_NAV;
	}
}
long long AbstractClient::getTime(){
	return _time;
}
void AbstractClient::setDisplayMode(DisplayMode dm, long long switchTime){
	this->disableInput();
	_dmSwitchTime = switchTime + _time;
	_dm = dm;
}
DisplayMode AbstractClient::getDisplayMode(){
	return _dm;
}

void AbstractClient::quit(){
	_quit = true;
}

/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  AbstractClient.cpp
 *  Interface for client
 *
 */

#include <AbstractClient.h>

AbstractClient::AbstractClient() {
	_drawer = NULL;
	_im = IM_NO_INPUT;
}

AbstractClient::~AbstractClient() {
	// TODO Auto-generated destructor stub
}

void AbstractClient::disableInput(){
	_im = IM_NO_INPUT;
}

void AbstractClient::enableKeyInput(void (*callback)(void*, char), void *obj){
	_im = IM_KEY_ACCEPT;
	_keyInCallback = callback;
	_keyInCallbackObj = obj;
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

void AbstractClient::asyncInputGetLine(void (*callback)(void*, std::string), void *obj){

}

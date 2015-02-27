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

void AbstractClient::quit(){
	_quit = true;
}

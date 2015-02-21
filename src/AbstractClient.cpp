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
}

AbstractClient::~AbstractClient() {
	// TODO Auto-generated destructor stub
}

void AbstractClient::paint(){

}

Drawer *AbstractClient::getDrawer()
{
	return _drawer;
}


/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  AbstractClient.h
 *  Interface for client
 *
 */

#ifndef ABSTRACTCLIENT_H_
#define ABSTRACTCLIENT_H_

#include "Drawer.h"

class AbstractClient {
public:
	AbstractClient();
	virtual ~AbstractClient();

	virtual void paint();

	Drawer *getDrawer();
protected:
	Drawer * _drawer;
};

#endif /* ABSTRACTCLIENT_H_ */

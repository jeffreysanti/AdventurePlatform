/*
 * Gateway.h
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#ifndef INCLUDE_GATEWAY_H_
#define INCLUDE_GATEWAY_H_

#include <set>
#include <string>
#include "AbstractClient.h"
#include "Actor.h"

class Space;

class Gateway {
public:

	Gateway(std::string uuid, Space *src, Space *dest, std::string primaryDirection);
	virtual ~Gateway();

	std::string getUUID();
	Space *getSource();
	Space *getDestination();
	std::string getPrimaryDirection();

	void addDirectionString(std::string alt);
	bool testDirection(std::string input);

	bool isEnabled();
	void setEnabled(bool enabled);

	virtual void outputToDrawer(Drawer *draw, DrawLayer *layer);

	virtual bool actorAttemptGateway(Actor *actor, AbstractClient *cli);

	// for sorting by direction string
	static bool compareGatewayStrings(Gateway* a, Gateway* b) { return (*a < *b); }
	bool operator<(const Gateway &rhs) const { return _primaryDirection < rhs._primaryDirection; }

private:

	Space *_src;
	Space *_dest;
	bool _enabled;
	std::string _uuid;

	std::string _primaryDirection;
	std::set<std::string> _dirs;

};

#endif /* INCLUDE_GATEWAY_H_ */

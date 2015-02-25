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
#include <memory>

class Space;
class Gateway;

class GatewayDisplayer{
public:
	virtual ~GatewayDisplayer();
	virtual void outputToDrawer(Drawer *draw, DrawLayer *layer);
	Gateway *gw;
};
class GatewayActorAttempter{
public:
	virtual ~GatewayActorAttempter();
	virtual bool actorAttemptGateway(Actor *actor, AbstractClient *cli);
	Gateway *gw;
};


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

	void outputToDrawer(Drawer *draw, DrawLayer *layer);
	bool actorAttemptGateway(Actor *actor, AbstractClient *cli);

	void setDisplayer(std::auto_ptr<GatewayDisplayer> disp);
	void setActorAttempter(std::auto_ptr<GatewayActorAttempter> attmpt);


	// for sorting by direction string
	static bool compareGatewayStrings(Gateway* a, Gateway* b) { return (*a < *b); }
	bool operator<(const Gateway &rhs) const { return _primaryDirection < rhs._primaryDirection; }

private:

	Space *_src;
	Space *_dest;
	bool _enabled;
	std::string _uuid;

	std::set<std::string> _dirs;

	GatewayDisplayer *_displayer;
	GatewayActorAttempter *_actorAttempter;

protected:

	std::string _primaryDirection;

};


#endif /* INCLUDE_GATEWAY_H_ */

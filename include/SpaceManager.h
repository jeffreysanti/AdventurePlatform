/*
 * SpaceManager.h
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#ifndef INCLUDE_SPACEMANAGER_H_
#define INCLUDE_SPACEMANAGER_H_

#include <map>
#include "Space.h"
#include "Gateway.h"


class SpaceManager {
public:

	SpaceManager();
	virtual ~SpaceManager();

	Space *newSpace(std::string uuid);

private:

	std::map<std::string, Space*> _S;
	std::map<std::string, Gateway*> _G;

};

#endif /* INCLUDE_SPACEMANAGER_H_ */

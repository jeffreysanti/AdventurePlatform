/*
 * Space.h
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#ifndef INCLUDE_SPACE_H_
#define INCLUDE_SPACE_H_

#include <map>
#include <vector>
#include <string>
#include "Drawer.h"

class Gateway;

class Space {
public:
	Space(std::string uuid);
	virtual ~Space();

	void setName(std::string name);
	std::string getName();

	void setDesc(std::string desc);
	std::string getDesc();

	std::string getUUID();

	void addGatewayOut(Gateway *gateway);

	Gateway *findGatewayOut(std::string in);

	virtual void outputToDrawer(Drawer *draw);

private:

	std::string _uuid;
	std::string _name;

	std::string _desc;

	std::vector<Gateway*> _D;

};

#endif /* INCLUDE_SPACE_H_ */

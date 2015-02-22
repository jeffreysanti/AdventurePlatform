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

class Gateway;

class Space {
public:
	Space(std::string uuid);
	virtual ~Space();

	void setName(std::string name);
	std::string getName();

	std::string getUUID();

	void addGatewayOut(Gateway *gateway);

private:

	std::string _uuid;
	std::string _name;

	std::vector<Gateway*> _D;

};

#endif /* INCLUDE_SPACE_H_ */

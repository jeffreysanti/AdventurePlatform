/*
 * ItemManager.h
 *
 *  Created on: Feb 28, 2015
 *      Author: jeffrey
 */

#ifndef INCLUDE_ITEMMANAGER_H_
#define INCLUDE_ITEMMANAGER_H_

#include <vector>
#include <map>
#include <set>
#include "Item.h"



class ItemManager {
public:
	ItemManager();
	virtual ~ItemManager();

	Item *newItem(std::string uuid);
	Item *newItem();

	void registerVerb(std::string vb);
	bool isVerb(std::string vb);


private:
	std::vector<Item*> _I;
	std::map<std::string, Item*> _IU;
	std::set<std::string> _V;
};

#endif /* INCLUDE_ITEMMANAGER_H_ */

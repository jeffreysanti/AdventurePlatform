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
#include <memory>
#include "Item.h"



class ItemManager {
public:
	ItemManager();
	virtual ~ItemManager();

	void registerItem(std::string uuid, std::auto_ptr<Item>);
	void registerItem(std::auto_ptr<Item>);

	void registerVerb(std::string vb);
	bool isVerb(std::string vb);


private:
	std::vector<Item*> _I;
	std::map<std::string, Item*> _IU;
	std::set<std::string> _V;
};

#endif /* INCLUDE_ITEMMANAGER_H_ */

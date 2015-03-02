/*
 * Item.h
 *
 *  Created on: Feb 28, 2015
 *      Author: jeffrey
 */

#ifndef INCLUDE_ITEM_H_
#define INCLUDE_ITEM_H_

#include <string>
#include <memory>
#include <set>
#include <algorithm>
#include <iostream>
#include "AbstractClient.h"

class Space;
class Actor;
class Item;

class Item {

	friend class ItemManager;

public:
	Item();
	virtual ~Item();

	std::string getClass();

	void setSpace(Space *space);
	Space *getSpace();

	void setPrimaryName(const std::string &s);
	std::string getPrimaryName();
	void addNameString(std::string s);

	bool testName(std::string s);

	virtual void outputToDrawer(Drawer *draw, DrawLayer *layer);
	virtual void onUse(std::string vb, Actor *actor, AbstractClient *cli);

protected:

	std::string _class;

	std::string _primaryName;
	std::set<std::string> _names;

	Space *_space;

private:

	void setUniqueUUID(bool unique, std::string uuid);

	std::string _uuid;
	bool _unique;
};

#endif /* INCLUDE_ITEM_H_ */

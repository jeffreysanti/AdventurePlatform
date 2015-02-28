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

class ItemDisplayer{
public:
	virtual ~ItemDisplayer();
	virtual void outputToDrawer(Drawer *draw, DrawLayer *layer);
	Item *item;
};

class ItemUser{
public:
	virtual ~ItemUser();
	virtual void useItem(std::string vb, Actor *actor, AbstractClient *cli);
	Item *item;
};



class Item {

	friend class ItemManager;

public:
	Item();
	virtual ~Item();

	std::string getClass();

	void setSpace(Space *space);
	Space *getSpace();

	void setPrimaryName(std::string s);
	std::string getPrimaryName();
	void addNameString(std::string s);

	bool testName(std::string s);

	void outputToDrawer(Drawer *draw, DrawLayer *layer);
	void setDisplayer(std::auto_ptr<ItemDisplayer> disp);

	void onUse(std::string vb, Actor *actor, AbstractClient *cli);
	void setUser(std::auto_ptr<ItemUser> user);

protected:

	std::string _class;

	std::string _primaryName;
	std::set<std::string> _names;

	Space *_space;

private:

	void setUniqueUUID(bool unique, std::string uuid);

	std::string _uuid;
	bool _unique;

	ItemDisplayer *_displayer;
	ItemUser *_user;
};

#endif /* INCLUDE_ITEM_H_ */

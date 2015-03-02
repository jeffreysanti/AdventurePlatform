/*
 * ItemManager.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: jeffrey
 */

#include <ItemManager.h>

ItemManager::ItemManager() {
	// TODO Auto-generated constructor stub

}

ItemManager::~ItemManager() {
	// TODO Auto-generated destructor stub
	for(int i=0; i<_I.size(); i++){
		delete _I[i];
	}
	_I.clear();

	for(std::map<std::string, Item*>::iterator it = _IU.begin(); it != _IU.end(); ++it){
		delete (*it).second;
	}
	_IU.clear();
}

void ItemManager::registerItem(std::string uuid, std::auto_ptr<Item> itm){
	Item *item = itm.release();
	if(uuid == ""){
		_I.push_back(item);
		item->setUniqueUUID(false, "");
	}else{
		if(_IU.find(uuid) != _IU.end()){
			std::cerr << "UNIQUE ITEM REGISTERED AGAIN!";
			exit(1);
		}
		_IU[uuid] = item;
		item->setUniqueUUID(true, uuid);
	}
}
void ItemManager::registerItem(std::auto_ptr<Item> itm){
	registerItem("", itm);
}

void ItemManager::registerVerb(std::string vb){
	std::transform(vb.begin(), vb.end(), vb.begin(), ::tolower);
	_V.insert(vb);
}
bool ItemManager::isVerb(std::string vb){
	return(_V.find(vb) != _V.end());
}



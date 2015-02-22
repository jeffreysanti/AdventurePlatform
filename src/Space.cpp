/*
 * Space.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#include <Space.h>
#include <algorithm>
#include <Gateway.h>

Space::Space(std::string uuid) {
	_uuid = uuid;
}

Space::~Space() {

}

void Space::setName(std::string name){
	_name = name;
}

std::string Space::getName(){
	return _name;
}

std::string Space::getUUID(){
	return _uuid;
}

void Space::addGatewayOut(Gateway *gateway){
	_D.push_back(gateway);
	std::sort(_D.begin(), _D.end(), Gateway::compareGatewayStrings);
}

void Space::outputToDrawer(Drawer *draw){
	draw->resetScreen(BLACK);

	DrawLayer *layerDesc = draw->newLayer(draw->getWidth(), draw->getHeight()/2 - 2);
	layerDesc->setOffset(0, 1);
	layerDesc->setColor(MAGENTA);
	layerDesc->solidFill();

	DrawLayer *layerFind = draw->newLayer((draw->getWidth() * 5 / 8)-1,
			draw->getHeight() - 2 - layerDesc->getEffectiveHeight());
	layerFind->setOffset(0, 2+layerDesc->getEffectiveHeight());
	layerFind->setColor(YELLOW);
	layerFind->solidFill();

	DrawLayer *layerExits = draw->newLayer(draw->getWidth() - 1 - layerFind->getEffectiveWidth() ,
			draw->getHeight() - 2 - layerDesc->getEffectiveHeight());
	layerExits->setOffset(1+layerFind->getEffectiveWidth(), 2+layerDesc->getEffectiveHeight());
	layerExits->setColor(CYAN);
	layerExits->solidFill();

	DrawLayer *divTitle = draw->newLayer(draw->getWidth(), 1);
	draw->printFormattedTextCenter(divTitle, "<D>%s", _name.c_str());

	DrawLayer *divFind = draw->newLayer(layerFind->getEffectiveWidth(), 1);
	divFind->setOffset(0, layerFind->getOffsetY()-1);
	draw->printFormattedTextCenter(divFind, "<7>You Find...");

	DrawLayer *divExits = draw->newLayer(layerExits->getEffectiveWidth(), 1);
	divExits->setOffset(layerExits->getOffsetX(), layerExits->getOffsetY()-1);
	draw->printFormattedTextCenter(divExits, "<7>Exits");
}




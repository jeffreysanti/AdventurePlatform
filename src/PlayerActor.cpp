/*
 * PlayerActor.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: jeffrey
 */

#include <PlayerActor.h>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <boost/algorithm/string.hpp>
#include "Gateway.h"

PlayerActor::PlayerActor(Space *space, AbstractClient *cli, ItemManager *im) : Actor(space) {
	_class = "player";
	_cli = cli;
	_IM = im;

	_cli->getDrawer()->resetScreen(BLACK);
	DrawLayerGroup grp = _cli->getDrawer()->printFormattedTextCenter(_cli->getDrawer()->newLayer(),
			"<D>Welcome Player!<7> Enter Your Name");
	grp.applyTransformation(0, 4);
	_name = _cli->inputGetLine();
	_oldDM = DM_CUSTOM_HOLD;
}

PlayerActor::~PlayerActor() {
	// TODO Auto-generated destructor stub
}

void PlayerActor::onUpdate(long long tick){
	DisplayMode dmNew = _cli->getDisplayMode();
	if(dmNew != _oldDM && dmNew == DM_PLAYER_NAV){
		showLocation();
		_cli->asyncInputGetLine(this);
	}
	_oldDM = dmNew;
}

void PlayerActor::showLocation(){
	_space->outputToDrawer(_cli->getDrawer());
}

void PlayerActor::recvChar(char c){

}
void PlayerActor::recvString(std::string s){
	boost::algorithm::to_lower(s);
	boost::algorithm::trim(s);

	std::string firstWord = s;
	if(firstWord.find(' ') != s.npos){
		boost::algorithm::erase_tail(firstWord, firstWord.length()-firstWord.find(' '));
	}

	if(s == "exit" || s == "q" || s == "quit"){
		_cli->quit();
		return;
	}else if(s == "help" || s == "h"){

	}else if(_IM->isVerb(firstWord)){
		std::string subject = s;
		boost::algorithm::erase_head(subject, subject.find(' ')+1);
		boost::algorithm::trim(subject);
		Item *item = _space->findItemIn(subject);
		if(item != NULL){
			item->onUse(firstWord, this, _cli);
		}
		if(_cli->getDisplayMode() == DM_PLAYER_NAV){
			showLocation();
		}
	}else{ // assume 'go' command
		if(boost::algorithm::starts_with(s, "go ")){ // remove "go" section
			boost::algorithm::erase_head(s, 2);
			boost::algorithm::trim_left(s);
		}
		Gateway *nav = _space->findGatewayOut(s);
		if(nav != NULL){
			nav->actorAttemptGateway(this, _cli);
		}
		if(_cli->getDisplayMode() == DM_PLAYER_NAV){
			showLocation();
		}
	}
	if(_cli->getDisplayMode() == DM_PLAYER_NAV){
		_cli->asyncInputGetLine(this);
	}
}





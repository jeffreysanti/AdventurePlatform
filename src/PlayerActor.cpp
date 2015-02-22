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

PlayerActor::PlayerActor(Space *space, AbstractClient *cli) : Actor(space) {
	_class = "player";
	_cli = cli;

	DrawLayerGroup grp = _cli->getDrawer()->printFormattedTextCenter(_cli->getDrawer()->newLayer(),
			"<D>Welcome Player!<7> Enter Your Name");
	grp.applyTransformation(0, 4);
	_name = _cli->inputGetLine();
	//_cli->asyncInputGetLine(&PlayerActor::__keyboardHandler, this);
}

PlayerActor::~PlayerActor() {
	// TODO Auto-generated destructor stub
}

void PlayerActor::onUpdate(long long tick){
	_cli->asyncInputGetLine(&PlayerActor::__keyboardHandler, this);
}

void PlayerActor::__keyboardHandler(void *self, std::string s){
	((PlayerActor*)self)->keyboardHandler(s);
}


void PlayerActor::keyboardHandler(std::string s){
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	if(s == "exit" || s == "q" || s == "quit"){
		exit(0);
	}
}





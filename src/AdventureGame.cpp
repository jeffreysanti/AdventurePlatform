/*
 *  Jeffrey Santi
 *  Adventure Platform
 *
 *  AdventureGame.cpp
 *  Game Container
 *
 */

#include "AdventureGame.h"
#include <unistd.h>


AdventureGame::AdventureGame(RunType rt) {
	_rt = rt;
	_quit = false;
	_ticks = 0;
}

AdventureGame::~AdventureGame() {
	// TODO Auto-generated destructor stub
}

void AdventureGame::__defaultKeyboardHandler(void *self, char c){
	((AdventureGame*)self)->defaultKeyboardHandler(c);
}
void AdventureGame::defaultKeyboardHandler(char c){
	if(c == 'q' || c == 'Q' || c == '\027'){
		_quit = true;
	}
}

int AdventureGame::mainLoop(AbstractClient *cli)
{
	if(_rt == RT_CLIENT){
		DrawLayerGroup grp = cli->getDrawer()->printFormattedTextCenter(cli->getDrawer()->newLayer(),
				"<5>[ <6>Th<3>e Game ]");
		grp.applyTransformation(0, 3);

		DrawLayer *layer = cli->getDrawer()->newLayer();
		layer->setOffset(0, 10);
		layer->setColor(MAGENTA);
		//layer->printTextWW("This is a test message. A most interesting message for information."
		//		" What can one do with such wisdom from %d this block of text?", 1729);

		cli->getDrawer()->printFormattedTextWW(layer, "<5>This is a test message. A <D>most<5> interesting"
						" message for information."
						" What can one do with such wisdom from %d this block of text?", 1729);

		cli->enableKeyInput(&AdventureGame::__defaultKeyboardHandler, this);

		cli->paint();
		while(!_quit){
			usleep(50000); // 1/20 sec tick

			// perform any updates
			if(_ticks % 20 == 0 && _ticks > 0)
				grp.applyTransformation(0, 1);

			if(_ticks > 60){
				std::string line = cli->inputGetLine();
			}

			// handle screen & input
			cli->paint();
			if(!cli->processInput())
				break;
			_ticks ++;
		}
		return 0;
	}
	return -1;
}

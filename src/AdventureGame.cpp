/*
 *  Jeffrey Santi
 *  Adventure Platform
 *
 *  AdventureGame.cpp
 *  Game Container
 *
 */

#include "AdventureGame.h"


AdventureGame::AdventureGame(RunType rt) {
	_rt = rt;

}

AdventureGame::~AdventureGame() {
	// TODO Auto-generated destructor stub
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

		cli->getDrawer()->printFormattedTextWW(layer, "<5>This is a test message. A <G>most<5> interesting"
						" message for information."
						" What can one do with such wisdom from %d this block of text?", 1729);

		cli->paint();
		while(true){
			::sleep(1);
			grp.applyTransformation(0, 1);
			cli->paint();
		}
		return 0;
	}
	return -1;
}

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

#include "PlayerActor.h"

#include <boost/python.hpp>
#include <Python.h>


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


extern "C" void initAdventurePlatform();

int AdventureGame::mainLoop(AbstractClient *cli)
{
	if(_rt == RT_CLIENT){
		//cli->getDrawer()->resetScreen(BLACK);
		//cli->disableInput();
		/*DrawLayerGroup grp = cli->getDrawer()->printFormattedTextCenter(cli->getDrawer()->newLayer(),
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

		cli->paint();*/

		Space *start = _S.newSpace("startPos");
		start->setName("Start Village");
		start->setDesc("You are in Dita Ba's antechamber. It is a small sealed room with three airtight"
			      " doors and a teleportation terminal back to Ke'Vr. To the south is a door with"
			      " yellow radiation symbol printed on it, and a small window where you can see"
			      " another door just beyond it. To the east the door says Millstone Drive and"
			      " Main Street is to the west.");

		Space *space3 = _S.newSpace("test");
		space3->setName("Blah");
		space3->setDesc("Haha");

		/*Space *s2 = _S.newSpace("mainSt");
		s2->setName("Main Street");
		s2->setDesc("Buildings line the north and south ends of Main Street. Westbound, there is"
		      " the town hall, and eastbound, the street ends leading back to the city's"
		      " antechamber. Sirens ring every couple minutes and dilapidated billboards"
		      " line the deserted street.");

		Gateway *g1 = _S.newGateway("start-mainSt", start, s2, "West to Main Street");
		g1->addDirectionString("west");
		g1->addDirectionString("main street");
		g1->addDirectionString("w");
		g1->addDirectionString("main st");
		g1->addDirectionString("main st.");
		g1->addDirectionString("main");
		Gateway *g2 = _S.newGateway("mainSt-start", s2, start, "East to Antechamber");
		g2->addDirectionString("east");
		g2->addDirectionString("e");
		g2->addDirectionString("antechamber");





		printf("\033[1;1fSTART:\n");
*/
		PyImport_AppendInittab( "AdventurePlatform", &initAdventurePlatform );


		PyObject *pName, *pModule, *pDict, *pFunc;
		PyObject *pArgs, *pValue;
		int i;

		if (3 < 3) {
			fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
			return 1;
		}

		Py_Initialize();

		char syspath[256];
		char pwd[256];

		PyRun_SimpleString("import sys");
		strcpy(syspath, "sys.path.append('");
		if (getcwd(pwd, sizeof(pwd)) != NULL)
			strcat(syspath, pwd);
		strcat(syspath, "')");
		PyRun_SimpleString(syspath);

		PyImport_ImportModule("AdventurePlatform");

		try{

			boost::python::object plugin = boost::python::import("gametest");
			boost::python::object plugin_namespace = plugin.attr("__dict__");

			plugin.attr("setup")(boost::python::ptr(&_S));


			_A.registerActor(new PlayerActor(start, cli));

		}catch( boost::python::error_already_set ){
			PyErr_Print();
			exit(1);
		}




		while(!_quit){

			try{
				usleep(50000); // 1/20 sec tick

				// perform any updates
				_A.onUpdate(_ticks);

				// handle screen & input
				cli->paint();
				if(!cli->processInput())
					break;
				_ticks ++;
			}catch( boost::python::error_already_set ){
				PyErr_Print();
				exit(1);
			}
		}
		return 0;
	}
	return -1;
}

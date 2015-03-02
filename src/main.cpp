/*
 *  Jeffrey Santi
 *  Adventure Platform
 *
 *  main.cpp
 *  Program Entry Point
 *
 */

#include "AdventureGame.h"
#include <cstdio>
#include "TerminalClient/TerminalClient.h"
#include "TerminalClient/TestingClient.h"

#include "angelscript.h"


/*
 *
 *    ***** ANGLESCRIPT REQUIRES: -fno-strict-aliasing for GNU C++
 *
 *
 */



//using namespace boost::python;

int main(int argc, char** argv)
{

	/*Py_Initialize();

	object result = eval("5 ** 2");
	int five_squared = extract<int>(result);

	printf("Value: %d", five_squared);*/

	if(argc > 1){
		TestingClient cli;

		AdventureGame game(RT_CLIENT);
		int ret = game.mainLoop(&cli);
		return ret;
	}else{
		TerminalClient cli;
		cli.promptForColorSupport();

		AdventureGame game(RT_CLIENT);
		int ret = game.mainLoop(&cli);
		return ret;
	}
	//TestingClient cli;

}






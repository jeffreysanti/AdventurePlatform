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
/*#include <boost/asio.hpp>
#include <boost/asio.hpp>
#include <boost/python.hpp>
#include <Python.h>*/

#include "TerminalClient/TerminalClient.h"

//using namespace boost::python;

int main(int argc, char** argv)
{
	/*Py_Initialize();

	object result = eval("5 ** 2");
	int five_squared = extract<int>(result);

	printf("Value: %d", five_squared);*/

	TerminalClient cli;
	cli.promptForColorSupport();

	AdventureGame game(RT_CLIENT);
	int ret = game.mainLoop(&cli);
	return ret;
}






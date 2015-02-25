

#include <boost/python.hpp>
using namespace boost::python;


#include "DrawLayer.h"
#include "Drawer.h"





void   	(DrawLayer::*printWWLayer)(std::string) = &DrawLayer::printTextWW;
void   	(DrawLayer::*printCenterLayer)(std::string) = &DrawLayer::printTextCenter;

void piExportDrawLayer(){
	enum_<Color>("Color")
	    .value("BLACK", BLACK)
	    .value("GREEN", GREEN)
		.value("BROWN", BROWN)
		.value("BLUE", BLUE)
		.value("MAGENTA", MAGENTA)
		.value("CYAN", CYAN)
		.value("GRAY", GRAY)
		.value("DARKGRAY", DARKGRAY)
		.value("LIGHTRED", LIGHTRED)
		.value("LIGHTGREEN", LIGHTGREEN)
		.value("YELLOW", YELLOW)
		.value("LIGHTBLUE", LIGHTBLUE)
		.value("LIGHTMAGENTA", LIGHTMAGENTA)
		.value("LIGHTCYAN", LIGHTCYAN)
		.value("WHITE", WHITE)
	    ;

	class_<DrawLayer, boost::noncopyable>("DrawLayer", init<Drawer*,int,int>())
			.def("solidFill", &DrawLayer::solidFill)
			.def("setChar", &DrawLayer::setChar)
			.def("setColor", &DrawLayer::setColor)
			.def("getColor", &DrawLayer::getColor)
			.def("setOffset", &DrawLayer::setOffset)
			.def("getOffsetX", &DrawLayer::getOffsetX)
			.def("getOffsetY", &DrawLayer::getOffsetY)
			.def("getCell", &DrawLayer::getCell)
			.def("getEffectiveWidth", &DrawLayer::getEffectiveWidth)
			.def("getEffectiveHeight", &DrawLayer::getEffectiveHeight)
			.def("printTextWW", printWWLayer)
			.def("printTextCenter", printCenterLayer)
			;

	class_<DrawLayerGroup>("DrawLayerGroup", init<std::vector<DrawLayer*> >())
			.def("applyTransformation", &DrawLayerGroup::applyTransformation)
			.def("colorMap", &DrawLayerGroup::colorMap)
			;
}




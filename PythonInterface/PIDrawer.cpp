

#include <boost/python.hpp>
using namespace boost::python;


#include "Drawer.h"


DrawLayer *   	(Drawer::*newLayer1)() = &Drawer::newLayer;
DrawLayer *   	(Drawer::*newLayer2)(Color) = &Drawer::newLayer;
DrawLayer *   	(Drawer::*newLayer3)(int,int) = &Drawer::newLayer;

DrawLayerGroup 	(Drawer::*printWW)(DrawLayer*,std::string) = &Drawer::printFormattedTextWW;
DrawLayerGroup 	(Drawer::*printCenter)(DrawLayer*,std::string) = &Drawer::printFormattedTextCenter;



void piExportDrawer(){
    class_<Drawer, boost::noncopyable>("Drawer", init<int,int,Color>())
        .def("newLayer", newLayer1, return_value_policy<reference_existing_object>())
        .def("newLayer", newLayer2, return_value_policy<reference_existing_object>())
		.def("newLayer", newLayer3, return_value_policy<reference_existing_object>())
		.def("getWidth", &Drawer::getWidth)
    	.def("getHeight", &Drawer::getHeight)
		.def("printFormattedTextWW", printWW)
		.def("printFormattedTextCenter", printCenter)
		;
}




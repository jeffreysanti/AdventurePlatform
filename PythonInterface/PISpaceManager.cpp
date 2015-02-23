

#include <boost/python.hpp>
using namespace boost::python;


#include "SpaceManager.h"



void piExportSpaceManager(){
    class_<SpaceManager>("SpaceManager")
        .def("newSpace", &SpaceManager::newSpace, return_value_policy<reference_existing_object>())
		.def("newGateway", &SpaceManager::newGateway, return_value_policy<reference_existing_object>())
		.def("getSpace", &SpaceManager::getSpace,  return_value_policy<reference_existing_object>())
    ;
}




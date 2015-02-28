

#include <boost/python.hpp>
using namespace boost::python;


#include "SpaceManager.h"
#include "Gateway.h"


/*class SpaceWrap : public Space, public wrapper<Space>
{
public:

	SpaceWrap(std::string s) : Space(s) {}



	void outputToDrawer(Drawer *draw)
	{
		if (override outputToDrawer = this->get_override("outputToDrawer"))
			outputToDrawer(draw); // *note*
		else
			Space::outputToDrawer(draw);
	}
	void default_outputToDrawer(Drawer *draw) { this->Space::outputToDrawer(draw); }
};
*/

void piExportSpace(){
    class_<Space, boost::noncopyable>("Space",init<std::string>())
        .def("setName", &Space::setName)
		.def("getName", &Space::getName)
		.def("setDesc", &Space::setDesc)
		.def("getDesc", &Space::getDesc)
		.def("getUUID", &Space::getUUID)
		.def("addGatewayOut", &Space::addGatewayOut)
		.def("outputToDrawer", &Space::outputToDrawer)
		.def("addItem", &Space::addItem)
    ;
    class_<SpaceManager>("SpaceManager")
		.def("newSpace", &SpaceManager::newSpace, return_value_policy<reference_existing_object>())
		.def("newGateway", &SpaceManager::newGateway, return_value_policy<reference_existing_object>())
		.def("getSpace", &SpaceManager::getSpace,  return_value_policy<reference_existing_object>())
	;
}




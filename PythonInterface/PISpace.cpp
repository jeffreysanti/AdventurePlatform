

#include <boost/python.hpp>
using namespace boost::python;


#include "Space.h"
#include "Gateway.h"


class SpaceWrap : public Space, public wrapper<Space>
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


void piExportSpace(){
    class_<SpaceWrap, boost::noncopyable>("Space",init<std::string>())
        .def("setName", &SpaceWrap::setName)
		.def("getName", &SpaceWrap::getName)
		.def("setDesc", &SpaceWrap::setDesc)
		.def("getDesc", &SpaceWrap::getDesc)
		.def("getUUID", &SpaceWrap::getUUID)
		.def("addGatewayOut", &SpaceWrap::addGatewayOut)
		.def("outputToDrawer", &Space::outputToDrawer, &SpaceWrap::default_outputToDrawer)
    ;
}




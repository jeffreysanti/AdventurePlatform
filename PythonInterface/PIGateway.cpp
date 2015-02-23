

#include <boost/python.hpp>
using namespace boost::python;


#include "Gateway.h"


class GatewayWrap : public Gateway, public wrapper<Gateway>
{
public:

	GatewayWrap(std::string uuid, Space *src, Space *dest, std::string primaryDirection) :
		Gateway(uuid, src, dest, primaryDirection) {}

	void outputToDrawer(Drawer *draw, DrawLayer *layer)
	{
		if (override outputToDrawer = this->get_override("outputToDrawer"))
			outputToDrawer(draw, layer); // *note*
		else
			Gateway::outputToDrawer(draw, layer);
	}
	void default_outputToDrawer(Drawer *draw, DrawLayer *layer) { this->Gateway::outputToDrawer(draw, layer); }

	bool actorAttemptGateway(Actor *actor, AbstractClient *cli)
	{
		if (override actorAttemptGateway = this->get_override("actorAttemptGateway"))
			return actorAttemptGateway(actor, cli); // *note*
		else
			return Gateway::actorAttemptGateway(actor, cli);
	}
	bool default_actorAttemptGateway(Actor *actor, AbstractClient *cli) {
		return this->Gateway::actorAttemptGateway(actor, cli);
	}


};


void piExportGateway(){
    class_<GatewayWrap, boost::noncopyable>("Gateway",init<std::string, Space *, Space *, std::string>())
        .def("getUUID", &GatewayWrap::getUUID)
		.def("getPrimaryDirection", &GatewayWrap::getPrimaryDirection)
		.def("getSource", &GatewayWrap::getSource, return_value_policy<reference_existing_object>())
		.def("getDestination", &GatewayWrap::getDestination, return_value_policy<reference_existing_object>())
		.def("addDirectionString", &GatewayWrap::addDirectionString)
		.def("testDirection", &GatewayWrap::testDirection)
		.def("isEnabled", &GatewayWrap::isEnabled)
		.def("setEnabled", &GatewayWrap::setEnabled)
		.def("outputToDrawer", &Gateway::outputToDrawer, &GatewayWrap::default_outputToDrawer)
		.def("actorAttemptGateway", &Gateway::actorAttemptGateway, &GatewayWrap::default_actorAttemptGateway)
    ;
}




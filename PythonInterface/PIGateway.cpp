

#include <boost/python.hpp>
#include "Python.h"
using namespace boost::python;


#include "Gateway.h"


/*class GatewayWrap : public Gateway, public wrapper<Gateway>
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


};*/


class GatewayDisplayerWrap : public GatewayDisplayer, public wrapper<GatewayDisplayer>
{
public:
	GatewayDisplayerWrap(PyObject *self_) : self(self_){
		Py_INCREF(self);
	}
	GatewayDisplayerWrap(PyObject* self_, const GatewayDisplayer& copy) :
			GatewayDisplayer(copy), self(self_) {
		Py_INCREF(self);
	}
	~GatewayDisplayerWrap(){
		Py_DECREF(self);
	}
	virtual void outputToDrawer(Drawer *draw, DrawLayer *layer)
	{
		call_method<void>(self, "outputToDrawer", boost::python::ptr(draw), boost::python::ptr(layer));
	}

	PyObject *self;
};




class GatewayActorAttempterWrap : public GatewayActorAttempter, public wrapper<GatewayActorAttempter>
{
public:
	bool actorAttemptGateway(Actor *actor, AbstractClient *cli)
	{
		this->get_override("actorAttemptGateway")();
	}
};


void piExportGateway(){
    class_<Gateway, boost::noncopyable>("Gateway",init<std::string, Space *, Space *, std::string>())
        .def("getUUID", &Gateway::getUUID)
		.def("getPrimaryDirection", &Gateway::getPrimaryDirection)
		.def("getSource", &Gateway::getSource, return_value_policy<reference_existing_object>())
		.def("getDestination", &Gateway::getDestination, return_value_policy<reference_existing_object>())
		.def("addDirectionString", &Gateway::addDirectionString)
		.def("testDirection", &Gateway::testDirection)
		.def("isEnabled", &Gateway::isEnabled)
		.def("setEnabled", &Gateway::setEnabled)
		.def("setDisplayer", &Gateway::setDisplayer)
		.def("setActorAttempter", &Gateway::setActorAttempter)
    ;
    class_<GatewayDisplayer, std::auto_ptr<GatewayDisplayerWrap>, boost::noncopyable >(
    		"GatewayDisplayer")
		.def("outputToDrawer", pure_virtual(&GatewayDisplayerWrap::outputToDrawer))
		.def_readwrite("gw", &GatewayDisplayerWrap::gw);
		;
	class_<GatewayActorAttempterWrap, std::auto_ptr<GatewayActorAttempterWrap>, boost::noncopyable >("GatewayActorAttempter")
		.def("actorAttemptGateway", pure_virtual(&GatewayActorAttempterWrap::actorAttemptGateway))
		.def_readwrite("gw", &GatewayActorAttempterWrap::gw);
		;

	//implicitly_convertible<std::auto_ptr<GatewayDisplayerWrapWarp>, std::auto_ptr<GatewayDisplayerWrap> >();
	implicitly_convertible<std::auto_ptr<GatewayDisplayerWrap>, std::auto_ptr<GatewayDisplayer> >();

	implicitly_convertible<std::auto_ptr<GatewayActorAttempterWrap>, std::auto_ptr<GatewayActorAttempter> >();
}




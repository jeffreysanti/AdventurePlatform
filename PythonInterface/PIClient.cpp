

#include <boost/python.hpp>
#include "Python.h"
using namespace boost::python;


#include "AbstractClient.h"



class InputReceiverWrap : public InputReceiver, public wrapper<InputReceiver>
{
public:
	InputReceiverWrap(PyObject *self_) : self(self_){
		Py_INCREF(self);
	}
	InputReceiverWrap(PyObject* self_, const InputReceiver& copy) : InputReceiver(copy), self(self_) {
		Py_INCREF(self);
	}
	virtual ~InputReceiverWrap(){
		Py_DECREF(self);
	}
	void recvChar(char c){
		call_method<void>(self, "recvChar", c);
	}
	void recvString(std::string s){
		call_method<void>(self, "recvString", s);
	}

	PyObject *self;
};



class AbstractClientWrap : public AbstractClient, public wrapper<AbstractClient>
{
public:

	void paint(){
		if (override f = this->get_override("paint"))
			f();
		AbstractClient::paint();
	}
	void default_paint() { this->AbstractClient::paint(); }


	void disableInput(){
		if (override f = this->get_override("disableInput"))
			f();
		AbstractClient::disableInput();
	}
	void default_disableInput() { this->AbstractClient::disableInput(); }


	std::string inputGetLine(){
		if (override f = this->get_override("inputGetLine"))
			return f();
		return AbstractClient::inputGetLine();
	}
	std::string default_inputGetLine() { return this->AbstractClient::inputGetLine(); }


	void asyncInputGetLine(InputReceiver *ir){
		if (override f = this->get_override("asyncInputGetLine"))
			f(ir);
		AbstractClient::asyncInputGetLine(ir);
	}
	void default_asyncInputGetLine(InputReceiver *ir) { this->AbstractClient::asyncInputGetLine(ir); }

	void enableKeyInput(InputReceiver *ir){
		if (override f = this->get_override("enableKeyInput"))
			f(ir);
		AbstractClient::enableKeyInput(ir);
	}
	void default_enableKeyInput(InputReceiver *ir) { this->AbstractClient::enableKeyInput(ir); }
};

void piExportClient(){

	enum_<DisplayMode>("DisplayMode")
		    .value("PlayerNavigation", DM_PLAYER_NAV)
		    .value("Custom", DM_CUSTOM_HOLD)
			.value("CustomTimed", DM_CUSTOM_TIMED)
			;

    class_<AbstractClientWrap, boost::noncopyable>("AbstractClient")
		.def("paint", &AbstractClient::paint, &AbstractClientWrap::default_paint)
		.def("disableInput", &AbstractClient::disableInput, &AbstractClientWrap::default_disableInput)
        .def("enableKeyInput", &AbstractClient::enableKeyInput, &AbstractClientWrap::default_enableKeyInput)
        .def("inputGetLine", &AbstractClient::inputGetLine, &AbstractClientWrap::default_inputGetLine)
        .def("asyncInputGetLine", &AbstractClient::asyncInputGetLine, &AbstractClientWrap::default_asyncInputGetLine)
        .def("quit", &AbstractClientWrap::quit)
        .def("getDrawer", &AbstractClientWrap::getDrawer, return_value_policy<reference_existing_object>())
		.def("getTime", &AbstractClientWrap::getTime)
		.def("setDisplayMode", &AbstractClientWrap::setDisplayMode)
		.def("getDisplayMode", &AbstractClientWrap::getDisplayMode)
		;

    class_<InputReceiver, std::auto_ptr<InputReceiverWrap>, boost::noncopyable>("InputReceiver")
    		.def("recvChar", &InputReceiverWrap::recvChar)
    		.def("recvString", &InputReceiverWrap::recvString)
    		;

	implicitly_convertible<InputReceiverWrap, InputReceiver>();
	implicitly_convertible<AbstractClientWrap, AbstractClient>();

}




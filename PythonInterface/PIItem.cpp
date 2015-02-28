

#include <boost/python.hpp>
#include "Python.h"
using namespace boost::python;


#include "ItemManager.h"
#include "Space.h"
#include "Actor.h"


class ItemDisplayerWrap : public ItemDisplayer, public wrapper<ItemDisplayer>
{
public:
	ItemDisplayerWrap(PyObject *self_) : self(self_){
		Py_INCREF(self);
	}
	ItemDisplayerWrap(PyObject* self_, const ItemDisplayer& copy) :
		ItemDisplayer(copy), self(self_) {
		Py_INCREF(self);
	}
	~ItemDisplayerWrap(){
		Py_DECREF(self);
	}
	void outputToDrawer(Drawer *draw, DrawLayer *layer)
	{
		call_method<void>(self, "outputToDrawer", boost::python::ptr(draw), boost::python::ptr(layer));
	}

	PyObject *self;
};

class ItemUserWrap : public ItemUser, public wrapper<ItemUser>
{
public:
	ItemUserWrap(PyObject *self_) : self(self_){
		Py_INCREF(self);
	}
	ItemUserWrap(PyObject* self_, const ItemUser& copy) :
		ItemUser(copy), self(self_) {
		Py_INCREF(self);
	}
	~ItemUserWrap(){
		Py_DECREF(self);
	}
	void useItem(std::string vb, Actor *actor, AbstractClient *cli){
		call_method<void>(self, "useItem", vb, boost::python::ptr(actor), boost::python::ptr(cli));
	}

	PyObject *self;
};

Item*   	(ItemManager::*newUnNamedI)() = &ItemManager::newItem;
Item*   	(ItemManager::*newNamedI)(std::string) = &ItemManager::newItem;


void piExportItem(){
    class_<Item, boost::noncopyable>("Item")
		.def("getPrimaryName", &Item::getPrimaryName)
		.def("setPrimaryName", &Item::setPrimaryName)
		.def("getSpace", &Item::getSpace, return_value_policy<reference_existing_object>())
		.def("addNameString", &Item::addNameString)
		.def("testName", &Item::testName)
		.def("setDisplayer", &Item::setDisplayer)
		.def("setUser", &Item::setUser)
    ;
    class_<ItemDisplayer, std::auto_ptr<ItemDisplayerWrap>, boost::noncopyable >(
    		"ItemDisplayer")
		.def("outputToDrawer", pure_virtual(&ItemDisplayerWrap::outputToDrawer))
		.def_readwrite("item", &ItemDisplayerWrap::item);
		;
	class_<ItemUser, std::auto_ptr<ItemUserWrap>, boost::noncopyable >(
			"ItemUser")
		.def("useItem", pure_virtual(&ItemUserWrap::useItem))
		.def_readwrite("item", &ItemUserWrap::item);
		;

	class_<ItemManager>("ItemManager")
		.def("newItem", newUnNamedI, return_value_policy<reference_existing_object>())
		.def("newUniqueItem", newNamedI, return_value_policy<reference_existing_object>())
		.def("registerVerb", &ItemManager::registerVerb)
	;

	implicitly_convertible<std::auto_ptr<ItemDisplayerWrap>, std::auto_ptr<ItemDisplayer> >();
	implicitly_convertible<std::auto_ptr<ItemUserWrap>, std::auto_ptr<ItemUser> >();
}




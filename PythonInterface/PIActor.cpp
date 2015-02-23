

#include <boost/python.hpp>
using namespace boost::python;


#include "Actor.h"


class ActorWrap : public Actor, public wrapper<Actor>
{
public:

	ActorWrap(Space *sp) : Actor(sp) {}

	void onUpdate(long long tick)
	{
		this->get_override("onUpdate")();
	}
};


void piExportActor(){
    class_<ActorWrap, boost::noncopyable>("Actor",init<Space*>())
        .def("getClass", &ActorWrap::getClass)
        .def("setSpace", &ActorWrap::setSpace)
		.def("onUpdate", pure_virtual(&ActorWrap::setSpace))
		;
}




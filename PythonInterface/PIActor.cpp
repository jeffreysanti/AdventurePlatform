

#include <boost/python.hpp>
using namespace boost::python;


#include "ActorManager.h"


class ActorWrap : public Actor, public wrapper<Actor>
{
public:

	ActorWrap(Space *sp) : Actor(sp) {}

	void onUpdate(long long tick)
	{
		this->get_override("onUpdate")();
	}
};

void   	(ActorManager::*regUnNamedA)(Actor*) = &ActorManager::registerActor;
void   	(ActorManager::*regNamedA)(std::string, Actor*) = &ActorManager::registerActor;


void piExportActor(){
    class_<ActorWrap, boost::noncopyable>("Actor",init<Space*>())
        .def("getClass", &ActorWrap::getClass)
        .def("setSpace", &ActorWrap::setSpace)
		.def("onUpdate", pure_virtual(&ActorWrap::setSpace))
		;

	void registerActor(Actor *actor);
    class_<ActorManager>("ActorManager")
		.def("registerActor", regUnNamedA)
		.def("registerUniqueActor", regNamedA)
	;
}




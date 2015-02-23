
#include <boost/python.hpp>
using namespace boost::python;

extern void piExportSpace();
extern void piExportActor();
extern void piExportSpaceManager();
extern void piExportGateway();


BOOST_PYTHON_MODULE(AdventurePlatform)
{
	piExportSpace();
	piExportActor();
	piExportGateway();
	piExportSpaceManager();
}


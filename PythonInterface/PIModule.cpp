
#include <boost/python.hpp>
using namespace boost::python;

extern void piExportSpace();
extern void piExportActor();
extern void piExportGateway();
extern void piExportItem();
extern void piExportDrawer();
extern void piExportDrawLayer();
extern void piExportClient();


BOOST_PYTHON_MODULE(AdventurePlatform)
{
	piExportSpace();
	piExportActor();
	piExportGateway();
	piExportItem();
	piExportDrawer();
	piExportDrawLayer();
	piExportClient();
}


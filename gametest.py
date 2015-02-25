from AdventurePlatform import *



def setup(SM):
	s2 = SM.newSpace("mainSt")
	s2.setName("Main Street")
	s2.setDesc("Buildings line the north and south ends of Main Street. Westbound, there is")
	
	g1 = SM.newGateway("start-mainSt", SM.getSpace("startPos"), s2, "West to Main Street")
	g1.addDirectionString("west");
	g1.addDirectionString("main street");
	g1.addDirectionString("w");
	g1.addDirectionString("main st");
	g1.addDirectionString("main st.");
	g1.addDirectionString("main");

	class testGW(GatewayDisplayer):
		def __init__(self):
			GatewayDisplayer.__init__(self)
			print("Initted testGW")
		
		def outputToDrawer(self, draw, layer):
			draw.printFormattedTextWW(layer, "Hello!!!")

	
	g1.setDisplayer(testGW());
	
	print(type(SM.getSpace("startPos")))
	print(type(testGW()))
	print(type(g1))
	print(type(SM))

	print(SM.getSpace("startPos"))
	print(testGW())
	print(g1)
	print(SM)

	print("HI")
	return 3


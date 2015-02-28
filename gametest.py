from AdventurePlatform import *



def setup(SM, IM, AM):
	
	IM.registerVerb("look")
	IM.registerVerb("use")
	
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
	
	
	class AppleDisplayer(ItemDisplayer):
		def outputToDrawer(self, draw, layer):
			draw.printFormattedTextWW(layer, "My Apples!!!")
	class AppleUser(ItemUser):
		def useItem(self, vb, actor, cli):
			cli.setDisplayMode(DisplayMode.CustomTimed, 40)
			drawer = cli.getDrawer()
			drawer.resetScreen(Color.BLACK)
			drawer.printFormattedTextCenter(drawer.newLayer(), "Yummy Apple")
	
	i = IM.newItem()
	i.setPrimaryName("Juicy Apples")
	i.setDisplayer(AppleDisplayer())
	i.setUser(AppleUser())
	s2.addItem(i)
	

	class testGW(GatewayDisplayer):
		def __init__(self):
			GatewayDisplayer.__init__(self)
			print("Initted testGW")
		
		def outputToDrawer(self, draw, layer):
			l = draw.printFormattedTextWW(layer, "Hello!!!")
			l.applyTransformation(1, 0)
			l.applyTransformation(1, 0)
	class something(InputReceiver):
		def __init__(self):
			InputReceiver.__init__(self)

	class noPass(GatewayActorAttempter, InputReceiver):
		def __init__(self):
			GatewayActorAttempter.__init__(self)
			InputReceiver.__init__(self)
		def actorAttemptGateway(self, actor, cli):
			cli.setDisplayMode(DisplayMode.Custom, 0)
			drawer = cli.getDrawer()
			drawer.resetScreen(Color.BLACK)
			drawer.printFormattedTextCenter(drawer.newLayer(), "You Shall Not Pass")
			lg = drawer.printFormattedTextCenter(drawer.newLayer(), "[Any Key To Continue]")
			lg.applyTransformation(0, 6)
			self.cli = cli
			self.actor = actor
			cli.asyncInputGetLine(self)
			return False
		def recvString(self, s):
			self.cli.setDisplayMode(DisplayMode.CustomTimed, 40)
			drawer = self.cli.getDrawer()
			drawer.resetScreen(Color.BLACK)
			drawer.printFormattedTextCenter(drawer.newLayer(), s)

	
	g1.setDisplayer(testGW());
	#g1.setActorAttempter(noPass());
	
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


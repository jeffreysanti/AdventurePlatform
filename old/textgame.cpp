#include "textgame.h"
#include "mainwindow.h"
#include "textbuffer.h"
#include "drawer.h"
#include "level.h"
#include "objectmangager.h"
#include "player.h"
#include "audiomanager.h"

TextAdventureGame::TextAdventureGame(MainWindow *w, void (*loadFunc)(TextAdventureGame*), QString name, QString intro)
{
	sName = name;
	sIntro = intro;

	player = NULL;

	OnLoad = NULL;
	OnSave = NULL;
	OnLoadLevels = loadFunc;

	QDir d(QCoreApplication::applicationDirPath()+"/save/");
	if(!d.exists())
	{
	    d = QDir(QCoreApplication::applicationDirPath());
	    d.mkdir("save/");
	}
	// in case it's ran from another path
	QDir::setCurrent(QCoreApplication::applicationDirPath());
	win = w;
	player = new Player(this);
	textbuffer = new TextBuffer(this);
	om = new ObjectManager(this);
	am = new AudioManager(this);
	win->game = this;

	oALev  = NULL;
	oARoom = NULL;
}

TextAdventureGame::~TextAdventureGame()
{
	if(player != NULL)
	{
		delete player;
		player = NULL;
	}
	if(textbuffer != NULL)
	{
		delete textbuffer;
		textbuffer = NULL;
	}
	if(om != NULL)
	{
		delete om;
		om = NULL;
	}
	if(am != NULL)
	{
		delete player;
		am = NULL;
	}
	for(QList<Level*>::iterator it=L.begin(); it!=L.end(); it++)
	{
		delete (*it);
	}
	L.clear();
}

void TextAdventureGame::BeginGame()
{
    while(true)
    {
	int cmd = ShowMenu(0);
	if(cmd == -1)
	{
	    exit(0);
	}
	if(cmd == 1) // new game
	{
	    StartNewGame();
	    return;
	}
	if(cmd == 2) // load
	{
	    if(LoadSavedGame())
	    {
		return;
	    }
	}
    }
}

int TextAdventureGame::ShowMenu(int status) // 0: just opended/game not loaded; 1: game in progress
{
	while(true)
	{
		textbuffer->AddText(textbuffer->Center(sName) + "\n\n");
		textbuffer->AddText(sIntro + "\n\n\n");

		if(status == 1)  textbuffer->AddText(textbuffer->Center("Resume Game") + "  [R]\n");
		textbuffer->AddText(textbuffer->Center("Start New Game") + "  [N]\n");
		textbuffer->AddText(textbuffer->Center("Load Game") + "  [L]\n");
		if(status == 1)  textbuffer->AddText(textbuffer->Center("Save Game") + "  [S]\n");
		textbuffer->AddText(textbuffer->Center("Quit") + "  [Q]\n");

		textbuffer->OutputBuffer(false);

		QString in;
		in = textbuffer->GetLine();
		if(textbuffer->bQuit)
		{
		    return -1;
		}

		if(textbuffer->Lower(in) == "new" || textbuffer->Lower(in) == "n")
		{
			return 1;
		}
		else if((textbuffer->Lower(in) == "resume" || textbuffer->Lower(in) == "r") && status == 1)
		{
			return 0;
		}
		else if(textbuffer->Lower(in) == "load" || textbuffer->Lower(in) == "l")
		{
			return 2;
		}
		else if((textbuffer->Lower(in) == "save" || textbuffer->Lower(in) == "s") && status == 1)
		{
			return 3;
		}
		else if(textbuffer->Lower(in) == "quit" || textbuffer->Lower(in) == "q")
		{
			return -1;
		}
		else
		{
		}
	}
}

void TextAdventureGame::StartNewGame()
{
	// clear other things
	if(player != NULL)
	{
		delete player;
		player = NULL;
	}
	if(L.size() > 0)
	{
		for(QList<Level*>::iterator it=L.begin(); it!=L.end(); it++)
		{
			delete (*it);
		}
		L.clear();
	}

	/*Cls();*/
	textbuffer->AddText("\n" + textbuffer->Center("[Enter Your Name And Hit Enter To Begin]"));
	textbuffer->OutputBuffer(false);
	QString in = textbuffer->GetLine();
	player = new Player(this);
	player->sName = in;
	OnLoadLevels(this);
	om->CheckForWarnings();
}

bool TextAdventureGame::LoadSavedGame()
{
    QList<QString> S;
    getdir("save\\*.sav", S);
    while(!textbuffer->bQuit)
    {
	textbuffer->AddText(textbuffer->Center("Load A Game")+"\n\n");
	for(int i=0; i<S.size(); i++)
	{
	    if(i % 3 == 0)
		textbuffer->AddText("\n");
	    QString s = S[i];
	    s = StrReplace(s, ".sav", "");
	    textbuffer->AddText(textbuffer->Left(s, floor(double((textbuffer->TEXT_COLS-1) / 3))));
	}
	textbuffer->AddText("\n\nName Or Quit > ");
	textbuffer->OutputBuffer(false);
	QString in = textbuffer->Lower(textbuffer->GetLine());
	if(in == "quit" || in == "exit")
	{
	    return false;
	}
	for(int i=0; i<S.size(); i++)
	{
	    if(in == textbuffer->Lower(StrReplace(S[i], ".sav", "")))
	    {
		// exists... load this
		// clear other things
		if(player != NULL)
		{
		    delete player;
		    player = NULL;
		}
		if(L.size() > 0)
		{
		    for(QList<Level*>::iterator it=L.begin(); it!=L.end(); it++)
		    {
			delete (*it);
		    }
		    L.clear();
		}
		// load normal lvls
		player = new Player(this);
		player->sName = in;
		OnLoadLevels(this);
		Load("save\\" + in + ".sav");
		return true;
	    }
	}
    }
    return false;
}

bool TextAdventureGame::SaveGame()
{
    QList<QString> S;
    getdir("save\\*.sav", S);
    while(!textbuffer->bQuit)
    {
	textbuffer->AddText(textbuffer->Center("Save Game")+"\n\n");
	for(int i=0; i<S.size(); i++)
	{
	    if(i % 3 == 0)
		textbuffer->AddText("\n");
	    QString s = S[i];
	    s = StrReplace(s, ".sav", "");
	    textbuffer->AddText(textbuffer->Left(s, floor(double((textbuffer->TEXT_COLS-1) / 3))));
	}
	textbuffer->AddText("\n\nSave Name Or Quit > ");
	textbuffer->OutputBuffer(false);
	QString in = textbuffer->Lower(textbuffer->GetLine());
	if(in == "quit" || in == "exit")
	{
	    return false;
	}
	if(StrReplace(in, " ", "") == "")
	{
	    continue;
	}
	bool reloop = false;
	for(int i=0; i<S.size(); i++)
	{
	    if(in == textbuffer->Lower(StrReplace(S[i], ".sav", "")))
	    {
		// exists... replace this?
		textbuffer->AddText(textbuffer->Center(StrReplace(S[i], ".sav", "")));
		textbuffer->AddText("\n\nReplace This? Yes No");
		textbuffer->OutputBuffer(false);
		QString conf = textbuffer->Lower(textbuffer->GetLine());
		if(conf == "yes" || conf == "y")
		{
		    break;
		}
		else
		{
		    reloop = true;
		    break; // no try again
		}
	    }
	}
	if(reloop)
	    continue;
	Save("save\\" + in + ".sav");
	return true;
    }
    return false;
}

Level *TextAdventureGame::AddLevel(QString name)
{
	Level *l = new Level(this, L.size()+1, name);
	L.push_back(l);
	return l;
}

void TextAdventureGame::StartNewLevel()
{
    if(player->GetCurrentRoom() != NULL)
    {
	om->ChangeLevel(player->GetCurrentLevelId(), player->GetCurrentRoom()->GetX(),
				player->GetCurrentRoom()->GetY());
    }
	int lid = player->GetCurrentLevelId()-1;
	player->_setLevel(L[lid]);
	player->_setRoom(L[lid]->GetRoom(L[lid]->startX, L[lid]->startY));
	if(player->GetCurrentRoom() == NULL)
	{
		textbuffer->AddText("\nERROR: LEVEL START POSITION NOT FOUND!\n");
	}
	UpdateAudio();
	textbuffer->AddText(textbuffer->Center(L[lid]->sLevelName) + "\n\n");
	textbuffer->AddText(L[lid]->sLevelIntro + "\n");

	textbuffer->OutputBuffer();
}

// CODES
//-1  : quit
// 0  : Hasn't returned yet
// 1  : first level
// 2  : change to new room
// 3  : Do nothing; re-look next loop
// 4  : look at object
// 5  : Use object
// 6  : take object
// 7  : new level
// 8  : inventory
// 9  : Read a book
// 10 : talk to character
// 11 : Drop an object

void TextAdventureGame::MessageLoop(int &code)
{
	if(player->ended) // game over
	{
		code = -1;
		return;
	}

	if(player->GetCurrentLevelId() < 1)
	{
		if(L.size() > 0)
		{
			player->_setLevelId(1);
			code = 1; // first level
			StartNewLevel();
		}
		else
		{
			code = -1;
			textbuffer->AddText("\nError: No Levels Loaded!\n\n");
			textbuffer->OutputBuffer();
		}
		return;
	}

	if(player->chLevel)
	{
		if(L.size() < player->GetCurrentLevelId() || player->GetCurrentLevelId() < 0)
		{
			code = -1;
			textbuffer->AddText("\nError: Level not found!\n\n");
			textbuffer->OutputBuffer();
			return;
		}
		code = 7; // next level
		StartNewLevel();
		player->chLevel = false;
		return;
	}

	if(player->GetCurrentRoom() == NULL)
	{
		code = -1;
		textbuffer->AddText("\nError: Room not found!\n\n");
		textbuffer->OutputBuffer();
		return;
	}

	// render "look"
	player->GetCurrentLevel()->Look();

	code = 0;
	while(code == 0)
	{
		if(textbuffer->bQuit)
		{
		    code = -1;
		    return;
		}
		textbuffer->OutputBuffer(false);
		// now do command
		QString input = textbuffer->Lower(textbuffer->GetLine());
		if(textbuffer->bQuit)
		{
		    code = -1;
		    return;
		}
		else if(input == "")
		{
		    code = 3; // just in case
		}
		else if(input == "menu" || input == "quit")
		{
			while(true)
			{
				int i = ShowMenu(1); // in-game menu
				if(i == -1) // quit
				{
					code = -1;
					return;
				}
				else if(i == 0) // resume
				{
					code = 3;
					break;
				}
				else if(i == 1) // new
				{
					StartNewGame();
					code = 1;
					return;
				}
				else if(i == 2) // load
				{
					code = 3;
					if(LoadSavedGame())
					    return;
				}
				else if(i == 3) // save
				{
					code = 3;
					if(SaveGame())
					return;
				}
			}
		}
		else if(input == "move east" || input == "east")
		{
			if(player->GetCurrentRoom()->rEast != NULL)
			{
				player->_setRoom(player->GetCurrentRoom()->rEast);
				UpdateAudio();
				code = 2;
			}
			else
			{
				textbuffer->AddText("Direction East is not possible\n");
				continue;
			}
		}
		else if(input == "move west" || input == "west")
		{
			if(player->GetCurrentRoom()->rWest != NULL)
			{
				player->_setRoom(player->GetCurrentRoom()->rWest);
				UpdateAudio();
				code = 2;
			}
			else
			{
				textbuffer->AddText("Direction West is not possible\n");
				continue;
			}
		}
		else if(input == "move north" || input == "north")
		{
			if(player->GetCurrentRoom()->rNorth != NULL)
			{
				player->_setRoom(player->GetCurrentRoom()->rNorth);
				UpdateAudio();
				code = 2;
			}
			else
			{
				textbuffer->AddText("Direction North is not possible\n");
				continue;
			}
		}
		else if(input == "move south" || input == "south")
		{
			if(player->GetCurrentRoom()->rSouth != NULL)
			{
				player->_setRoom(player->GetCurrentRoom()->rSouth);
				UpdateAudio();
				code = 2;
			}
			else
			{
				textbuffer->AddText("Direction South is not possible\n");
				continue;
			}
		}
		else if(input == "look" || input == "describe") // describe whole room
		{
			code = 3;
		}
		else if(StrContains(input, "look") || StrContains(input, "describe")) // describe object
		{
		    Object *o = om->GetObject(StrReplace(StrReplace(input, "describe ", ""), "look ", ""),
					      player->GetCurrentLevelId(), player->GetCurrentRoom()->GetX(),
					      player->GetCurrentRoom()->GetY(), true);
		    if(o == NULL)
		    {
			textbuffer->AddText("Object not found\n");
			continue;
		    }
		    o->Look();
		    code = 4;
		}
		else if(StrContains(input, "use") || StrContains(input, "press")) // use object
		{
		    Object *o = om->GetObject(StrReplace(StrReplace(input, "press ", ""), "use ", ""),
					      player->GetCurrentLevelId(), player->GetCurrentRoom()->GetX(),
					      player->GetCurrentRoom()->GetY(), true);
		    if(o == NULL)
		    {
			textbuffer->AddText("Object not found\n");
			continue;
		    }
		    o->Use();
		    code = 5;
		}
		else if(StrContains(input, "take") || StrContains(input, "pickup")) // use object
		{
		    Object *o = om->GetObject(StrReplace(StrReplace(input, "pickup ", ""), "take ", ""),
					      player->GetCurrentLevelId(), player->GetCurrentRoom()->GetX(),
					      player->GetCurrentRoom()->GetY(), false);
		    if(o == NULL)
		    {
			textbuffer->AddText("Object not found\n");
			continue;
		    }
		    o->Take();
		    code = 6;
		}
		else if(input == "inventory" || input == "items")
		{
			player->ShowInventory();
			code = 8;
		}
		else if(StrContains(input, "read")) // use object
		{
		    Object *o = om->GetObject(StrReplace(input, "read ", ""),
					      player->GetCurrentLevelId(), player->GetCurrentRoom()->GetX(),
					      player->GetCurrentRoom()->GetY(), true);
		    if(o == NULL)
		    {
			textbuffer->AddText("Object not found\n");
			continue;
		    }
		    if(o->type != OBJ_BOOK)
		    {
			textbuffer->AddText("Object is not a book\n");
			continue;
		    }
		    ((BookObject*)o)->Read();
		    code = 9;
		}
		else if(StrContains(input, "talk") || StrContains(input, "ask")) // talk to character
		{
		    Object *o = om->GetObject(StrReplace(StrReplace(input, "ask ", ""), "talk ", ""),
					      player->GetCurrentLevelId(), player->GetCurrentRoom()->GetX(),
					      player->GetCurrentRoom()->GetY(), false);
		    if(o == NULL)
		    {
			textbuffer->AddText("Object not found\n");
			continue;
		    }
		    if(o->type != OBJ_CHARACTER)
		    {
			textbuffer->AddText("You cannot talk to this object! Psycho!\n");
			continue;
		    }
		    ((CharacterObject*)o)->Talk();
		    code = 10;
		}
		else if(StrContains(input, "drop") || StrContains(input, "leave")) // use object
		{
		    Object *o = om->GetObject(StrReplace(StrReplace(input, "leave ", ""), "drop ", ""),
					      -1, 0, 0, true);
		    if(o == NULL)
		    {
			textbuffer->AddText("Object not found\n");
			continue;
		    }
		    o->Drop();
		    code = 11;
		}
		else if(input == "help" || input == "h")
		{
			textbuffer->AddText(textbuffer->Center("Help Menu") + "\n\n");
			textbuffer->AddText(textbuffer->Left(" menu[quit]", 25) + "Shows the main menu.\n");
			textbuffer->AddText(textbuffer->Left(" help[h]", 25) + "Shows the main menu.\n");
			textbuffer->AddText(textbuffer->Left(" look[describe]", 25) + "Describes where you are.\n");
			textbuffer->AddText(textbuffer->Left(" move <direction>", 25) + "Moves character in a cardinal direction.\n");
			textbuffer->AddText(textbuffer->Left(" east", 25) + "Moves character to the east.\n");
			textbuffer->AddText(textbuffer->Left(" west", 25) + "Moves character to the west.\n");
			textbuffer->AddText(textbuffer->Left(" north", 25) + "Moves character to the north.\n");
			textbuffer->AddText(textbuffer->Left(" south", 25) + "Moves character to the south.\n");
			textbuffer->AddText(textbuffer->Left(" look[describe] <object>", 25) + "Descibes an object in your area.\n");
			textbuffer->AddText(textbuffer->Left(" use[press] <object>", 25) + "Uses an object in the area or in your inventory.\n");
			textbuffer->AddText(textbuffer->Left(" take[pickup] <object>", 25) + "Takes an object from the area: stores in inventory.\n");
			textbuffer->AddText(textbuffer->Left(" drop[leave] <object>", 25) + "Drops an object into the area from inventory.\n");
			textbuffer->AddText(textbuffer->Left(" read <object>", 25) + "Reads a book or page.\n");
			textbuffer->AddText(textbuffer->Left(" talk[ask] <object>", 25) + "Talks to a character.\n");
		}
		else
		{
			textbuffer->AddText("Command not understood\n");
			continue;
		}
	}
	// now go to level rules function
	if(player->GetCurrentLevel()->OnApplyRules != NULL)
	{
		player->GetCurrentLevel()->OnApplyRules(this);
	}
}

Level *TextAdventureGame::GetLevel(int id)
{
	if(id < 1 || id > L.size())
	{
		return NULL;
	}
	return L[id-1];
}
Level *TextAdventureGame::GetLevel(QString name)
{
    for(int i=0; i<L.size(); i++)
    {
	if(textbuffer->Lower(L[i]->sLevelName) == textbuffer->Lower(name))
	{
	    return L[i];
	}
    }
    return NULL;
}

void TextAdventureGame::Save(QString fname)
{
    QFile f(fname);
    f.open(QIODevice::WriteOnly);
    QDataStream out(&f);

    out << (quint32)0xABC001;
    out << (qint32)10;

    out.setVersion(QDataStream::Qt_4_0);

    // first player
    player->Save(out); // save position & name
    om->Save(out); // save objects that moved & where they are

    out << L.size();
    for(int i=0; i<L.size(); i++) // open / closed doors in level
    {
	L[i]->Save(out);
    }

    if(OnSave != NULL)
	OnSave(out, this);

    f.close();
}

void TextAdventureGame::Load(QString fname)
{
    QFile f(fname);
    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);

    quint32 magic;
    in >> magic;
    if (magic != 0xABC001)
    {
	QMessageBox::warning(0, "Error", "Load Failed: Magic Number");
	return;
    }

    // Read the version
    qint32 version;
    in >> version;
    if (version != 10)
    if (magic != 0xABC001)
    {
	QMessageBox::warning(0, "Error", "Load Failed: Magic Number");
	return;
    }
    in.setVersion(QDataStream::Qt_4_0);

    player->Load(in); // get position & name
    om->Load(in); // find objects - where they are
    int levs = 0;
    in >> levs;

    QString lName;
    for(int i=0; i<levs; i++) // open / closed doors in level
    {
	in >> lName;
	GetLevel(lName)->Load(in);
    }

    if(OnLoad != NULL)
	OnLoad(in, this);

    f.close();
}

void TextAdventureGame::UpdateAudio()
{
    if(oALev != NULL && oARoom != NULL)
    {
	// stop preveous ones
	if(oARoom != player->GetCurrentRoom())
	{
	    if(oARoom->OnExitRoom != NULL)
		oARoom->OnExitRoom(this);
	    oARoom->EndAmbient();

	    if(player->GetCurrentRoom()->OnEnterRoom != NULL)
		player->GetCurrentRoom()->OnEnterRoom(this);
	}
	if(oALev != player->GetCurrentLevel())
	{
	    if(oALev->OnExitLevel != NULL)
		oALev->OnExitLevel(this);
	    oALev->EndAmbient();

	    player->GetCurrentLevel()->StartAmbient();
	    if(oALev->OnEnterLevel != NULL)
		oALev->OnEnterLevel(this);
	}
    }
    if(oALev == NULL)
    {
	player->GetCurrentLevel()->StartAmbient();
	if(player->GetCurrentLevel()->OnEnterLevel != NULL)
	    player->GetCurrentLevel()->OnEnterLevel(this);
	if(player->GetCurrentRoom()->OnEnterRoom != NULL)
	    player->GetCurrentRoom()->OnEnterRoom(this);
    }

    oALev = player->GetCurrentLevel();
    oARoom = player->GetCurrentRoom();

    oALev->PauseAmbient(true);
    if(!oARoom->StartAmbient())
    {
	oALev->PauseAmbient(false);
    }
}


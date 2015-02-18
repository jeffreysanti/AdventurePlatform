#include "game.h"


void DeComTerminal(Object *o, TextAdventureGame *game)
{
    QString lName = game->player->GetCurrentLevel()->sLevelName;
    int lid=0;
    for(int i=0; i<W.size(); i++)
    {
	if(game->textbuffer->Lower(lName) == game->textbuffer->Lower(W[i].name))
	{
	    lid = i;
	    break;
	}
    }
    QString in;
    int x = 2;
    while(x <= 21)
    {
	Drawer d;
	Layer l("bg", LT_BACK);
	l.str =
"<F0>"+UC_TL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_TR_CNR+"\n"
""+UC_VERT+"                           ___                            "+UC_VERT+"\n"
""+UC_VERT+"                          [\\ /]                           "+UC_VERT+"\n"
""+UC_VERT+"                          [ | ]                           "+UC_VERT+"\n"
""+UC_VERT+"                           ¯¯¯                            "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_BL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_BR_CNR+"\n";
	d.AddLayer(l);
	l = Layer("deCom", LT_FLOAT, '\0');
	l.str = "<F0>\n\n\n\n\n";
	l.str += game->textbuffer->Times(" ", x) + "________     _________                \n";
	l.str += game->textbuffer->Times(" ", x) + "___  __ \\______  ____/____________   \n";
	l.str += game->textbuffer->Times(" ", x) + "__  / / /  _ \\  /    _  __ \\_  __ \\\n";
	l.str += game->textbuffer->Times(" ", x) + "_  /_/ //  __/ /___  / /_/ /  / / /   \n";
	l.str += game->textbuffer->Times(" ", x) + "/_____/ \\___/\\____/  \\____//_/ /_/ \n";
	d.AddLayer(l);
	game->textbuffer->AddText(d.ToText());
	game->textbuffer->OutputBuffer(false);
	game->textbuffer->Wait(100);
	x++;
    }
    while(!game->textbuffer->bQuit)
    {
	Drawer d;
	Layer l("bg", LT_BACK);
	l.str =
"<F0>"+UC_TL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_TR_CNR+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_BL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_BR_CNR+"\n";
	d.AddLayer(l);
	l = Layer("warn", LT_FLOAT, '\0');
	l.str = "<F0>\n\n";
	l.str+= "  Warning, DeComp decompresses this canister. Doing\n"
		"  so destroys everything in this canister. Please\n"
		"  have all people evacuated before entering the\n"
		"  password to depressurize. Please note that once the\n"
		"  correct password is entered, this machine will wait\n"
		"  for confirmation from a KWA official. Once it is\n"
		"  confirmed, you will see that you have thirty minutes\n"
		"  to leave, before all is lost.\n\n"
		"  Enter The Password, Or Enter Quit To End Process.";
	d.AddLayer(l);
	game->textbuffer->AddText(d.ToText());
	game->textbuffer->OutputBuffer(false);
	in = game->textbuffer->GetLine();
	if(game->textbuffer->Lower(in) == "quit")
	{
	    return;
	}
	if(in == W[lid].dComPwd)
	{
	    d = Drawer();
	    l = Layer("bg", LT_BACK, '\0');
	    l.str =
    "<F0>"+UC_TL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_TR_CNR+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_BL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_BR_CNR+"\n";
	    d.AddLayer(l);
	    l = Layer("msg", LT_FLOAT, '\0');
	    l.str = "<F0>\n\n";
	    l.str += "  Message Sent:\n"
		     "     DeComp Permission For:\n"
		     "     "+lName+"\n"
		     "     Password Correct"
		     "     Proceed?\n\n";
	    l.str += "  Awaiting Responce...";
	    d.AddLayer(l);
	    game->textbuffer->AddText(d.ToText());
	    game->textbuffer->OutputBuffer(false);
	    game->textbuffer->Wait(10000);

	    d = Drawer();
	    l = Layer("bg", LT_BACK, '\0');
	    l.str =
    "<F0>"+UC_TL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_TR_CNR+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_VERT+"                                                          "+UC_VERT+"\n"
    ""+UC_BL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_BR_CNR+"\n";
	    d.AddLayer(l);
	    l = Layer("msg", LT_FLOAT, '\0');
	    l.str = "<F0>\n\n";
	    l.str += "  Message Sent:\n"
		     "     DeComp Permission For:\n"
		     "     "+lName+"\n"
		     "     Password Correct"
		     "     Proceed?\n\n";
	    l.str += "  Awaiting Responce...\n\n";
	    l.str += "  <FC>Request Accepted. You Have Thirty Minutes";
	    d.AddLayer(l);
	    game->textbuffer->AddText(d.ToText());
	    game->textbuffer->OutputBuffer(false);
	    game->textbuffer->Wait(4000);
	    o->OnUse = NULL;
	    o->sLookDescription = "It says you better get going.";
	    o->sUseText = "It says you need to move! It gave you thirty minutes you already"
			  " used it so why are you still here?";
	    W.removeAt(lid); // remove from list ... it doesn't exist anymore does it?
	    return;
	}
    }
}

void ToKeVrTerminal(Object *o, TextAdventureGame *game)
{
    game->am->StartAudio("audio/nxusBookButton_UpDown.ogg");
    QString lName = game->player->GetCurrentLevel()->sLevelName;
    int in;

    Drawer d;
    Layer l("bg", LT_BACK);
    l.str =
"<1A>"+UC_TL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_TR_CNR+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_BL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_BR_CNR+"\n";
    d.AddLayer(l);

    l = Layer("Welcome", LT_FLOAT, '\0');
    l.str = "<1A>\n "+game->textbuffer->Center(lName, 60) +"\n\n\n";
    l.str += "   1 - [TELEPORT TO KE'VR]\n";
    l.str += "   0 - [QUIT]\n";
    d.AddLayer(l);

    game->textbuffer->AddText(d.ToText());
    game->textbuffer->OutputBuffer(false);

    while(!game->textbuffer->bQuit)
    {
	Drawer d;
	Layer l("bg", LT_BACK);
	l.str =
"<1A>"+UC_TL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_TR_CNR+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_BL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_BR_CNR+"\n";
	d.AddLayer(l);

	l = Layer("Welcome", LT_FLOAT, '\0');
	l.str = "<1A>\n "+game->textbuffer->Center(lName, 60) +"\n\n\n";
	l.str += "   1 - [TELEPORT TO KE'VR]\n";
	l.str += "   0 - [QUIT]\n";
	d.AddLayer(l);

	game->textbuffer->AddText(d.ToText());
	game->textbuffer->OutputBuffer(false);
	in = game->textbuffer->GetNumber();
	if(in == 0)
	    return;
	else if(in == 1)
	{
	    game->player->GotoLevel("Ke'Vr");
	    return;
	}
    }
}

void OnUseTerminal(Object *o, TextAdventureGame *game)
{
    game->am->StartAudio("audio/nxusBookButton_UpDown.ogg");
    int page = 1; // 0=no page - on world info; -1=quit; -2=teleport to
    int id = -1; // current world selected
    int in;
    while(!game->textbuffer->bQuit)
    {
	QList<Choice> C;
	Drawer d;
	Layer l("bg", LT_BACK);
	l.str =
"<5E>"+UC_TL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_TR_CNR+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_VERT+"                                                          "+UC_VERT+"\n"
""+UC_BL_CNR+game->textbuffer->Times(UC_HORIZ, 58)+UC_BR_CNR+"\n";
	d.AddLayer(l);
	if(page == -1)
	{
	    return;
	}
	else if(page > 0)
	{
	    int x =1;
	    l = Layer("Welcome", LT_FLOAT, '\0');
	    l.str = "<5E>\n "+game->textbuffer->Center("Welcome To Ke'Vr", 60) +"\n\n\n";
	    d.AddLayer(l);
	    l = Layer("list", LT_FLOAT, '\0'); // '\0' won't be in the description name
	    l.str = "<5E>\n\n\n\n";
	    for(int i=(page-1)*7; i<W.size(); i++)
	    {
		Choice c;
		c.num = x;
		c.pg = 0;
		c.wid = i;
		C.push_back(c);
		if(W[i].pwd != "")
		    l.str += "<5C>";
		l.str += "   "+QString::number(x)+" - "	+ W[i].name+"\n";
		if(W[i].pwd != "")
		    l.str += "<5E>";
		x++;
		if(x > 7)
		    break;
	    }
	    for(int i=x; i<8; i++)
	    {
		l.str += "\n";
	    }

	    if(W.size() > page*7)
	    {
		l.str += "   8 - [NEXT PAGE]\n";
		Choice c;
		c.num = 8;
		c.pg = page+1;
		c.wid = -1;
		C.push_back(c);
	    }
	    else l.str += "\n";

	    if(page > 1)
	    {
		l.str += "   9 - [PREV PAGE]\n";
		Choice c;
		c.num = 9;
		c.pg = page-1;
		c.wid = -1;
		C.push_back(c);
	    }
	    else l.str += "\n";

	    l.str += "   0 - [QUIT]\n";
	    Choice c;
	    c.num = 0;
	    c.pg = -1;
	    c.wid = -1;
	    C.push_back(c);

	    d.AddLayer(l);
	    game->textbuffer->AddText(d.ToText());
	}
	else if(page == 0)
	{
	    l = Layer("world", LT_FLOAT, '\0');
	    l.str = "<5E>\n "+game->textbuffer->Center(W[id].name, 60) +"\n\n";
	    l.str += W[id].desc;
	    d.AddLayer(l);
	    l = Layer("buttons", LT_FLOAT, '\0');
	    l.str = "<5E>\n\n\n\n\n\n\n\n\n\n\n\n\n";

	    l.str += "   1 - [TELEPORT]\n";
	    Choice c;
	    c.num = 1;
	    c.pg = -2;
	    c.wid = id;
	    C.push_back(c);

	    l.str += "   0 - [QUIT]\n";
	    c.num = 0;
	    c.pg = ceil((double)(id+1)/7.0);
	    c.wid = -1;
	    C.push_back(c);

	    d.AddLayer(l);
	    game->textbuffer->AddText(d.ToText());
	}
	else if(page == -2)
	{
	    if(W[id].pwd != "")
	    {
		l = Layer("world", LT_FLOAT, '\0');
		l.str = "<5E>\n "+game->textbuffer->Center(W[id].name, 60) +"\n\n";
		l.str += "  <5C>PASSWORD REQUIRED: ENTER BELOW<5E>\n";
		d.AddLayer(l);
		game->textbuffer->AddText(d.ToText());
		game->textbuffer->OutputBuffer(false);
		QString sin = game->textbuffer->GetLine();
		if(sin == W[id].pwd && W[id].pwd != "*")
		{
		    game->player->GotoLevel(W[id].name);
		    return;
		}
		else
		{
		    page = 0;
		    continue;
		}
	    }
	    game->player->GotoLevel(W[id].name);
	    return;
	}
	else
	{
	    return;
	}

	game->textbuffer->OutputBuffer(false);
	in = game->textbuffer->GetNumber();
	for(int i=0; i<C.size(); i++)
	{
	    if(C[i].num == in)
	    {
		page = C[i].pg;
		id = C[i].wid;
		break;
	    }
	}
    }
}

void Save_KeVr(QDataStream &out, Level *l, TextAdventureGame *game)
{
    out << W;
}

void Load_KeVr(QDataStream &in, Level *l, TextAdventureGame *game)
{
    in >> W;
}

void Create_KeVr(TextAdventureGame *game, Level *l)
{
    // build the level
    Room  *r;
    Object *o;
    /*BookObject *bo;
    Page *pg;
    CharacterObject *co;*/
    Drawer d;
    Layer y;

    o = game->player->NewObject("Console:cmd", OS_PLAYER);
    o->sLookDescription = "Allows you to type in commands";

    r = l->AddRoom(0, 0, "Hallway 3");
    r->sDescription = "Along the plastic looking white walls, you see prited clearly:\n\n"
		      "        [3 : 27]\n"
		      "        ["+UC_KR_3+" : "+UC_KR_2+UC_KR_7+"]\n\n"
		      "Teleporter terminals line the walls, and people walk back and forth trying to find"
		      " an avalible one without walking to the next hallway, which is closed.";

    o = r->NewObject("Terminal:computer:teleporter");
    o->sLookDescription = "It is a circular base with a glass tube that comes down."
			  " There is a touch screen where you select the can to travel"
			  " to (only the touch doesn't apply to you.)";
    o->sUseText = "";
    o->OnUse = &OnUseTerminal;

    l->OpenAllDoors();
    l->sLevelIntro = "You arrive in the busy corridores of Ke'vr.";
    l->startX = 0;
    l->startY = 0;
    l->OnLoad = &Load_KeVr;
    l->OnSave = &Save_KeVr;

    l->AddAmbientMusic("audio/OverCoat__Memories_EP__1__Reflections_64kb.mp3");
    l->AddAmbientMusic("audio/ercaMusSeg02-1.ogg");
}


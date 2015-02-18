#include "characterobject.h"
#include "textgame.h"


DialogOptions::DialogOptions(TextAdventureGame *g)
{
    game = g;
}

DialogOptions::~DialogOptions()
{
}

void DialogOptions::AddOption(QString name, QString text)
{
	DialogOpt o;
	o.name = name;
	o.text = text;
	O.push_back(o);
}

void DialogOptions::RemoveOption(QString name)
{
	for(std::vector<DialogOpt>::iterator it=O.begin(); it!=O.end(); it++)
	{
		if((*it).name == name)
		{
			O.erase(it);
			return;
		}
	}
}

QString DialogOptions::ShowOptions()
{
	/*Cls();*/ // do handle cls work, because this is used in GameSpecific code. -- Don't make level designer do that

	while(true)
	{
		game->textbuffer->AddText("What would you say?\n\n");
		int i=1, in;
		QString sin;
		for(std::vector<DialogOpt>::iterator it=O.begin(); it!=O.end(); it++)
		{
		    game->textbuffer->AddText(" " + game->textbuffer->Right(game->textbuffer->Int(i), 3) + ") " +
					(*it).text + "\n");
		    i++;
		}
		game->textbuffer->AddText(" " + game->textbuffer->Right(game->textbuffer->Int(i), 3) + ") " +
				    "Nether mind." + "\n\n");
		game->textbuffer->OutputBuffer(false);
		in = game->textbuffer->GetLine().toInt();
		if(game->textbuffer->bQuit)
		{
		    return "";
		}
		if(in == i)
			return "";
		i = 1;
		for(std::vector<DialogOpt>::iterator it=O.begin(); it!=O.end(); it++)
		{
			if(i == in)
				return game->textbuffer->Lower((*it).name);
			i++;
		}
		game->textbuffer->AddText("You cannot say that.\n\n\n");
	}
}


CharacterObject::CharacterObject(TextAdventureGame *g, QString name, ObjScope scope, int lev, int x, int y)
				: Object(g, name, scope, lev, x, y)
{
	type = OBJ_CHARACTER;
	OnTalk = NULL;
	sName = name;
}

CharacterObject::~CharacterObject()
{
}


void CharacterObject::Talk()
{
	if(OnTalk == NULL)
	{
	    game->textbuffer->AddText("I'm sorry, that person cannot be reached. Please walk away and try your talk later. If you continue to have this"
			" problem, contact your level designer immediately. It is possible he made a mistake as to not assign a function to handle this"
			" conversation. Again this may or may not be your fault, but the person can not be reached. If you do not press enter and"
			" the person decides to talk, you will be charged one dollar. Checks can be mailed to Global T&T at 100 Web Street, Littleville, MT"
			" 02425. If you do not wish to make a payment press the key I told you to press. Right now! Seriously why are you still listening?"
			" Go! I really don't have the time to cash a check. PLEASE LEAVE NOW!");
	    game->textbuffer->OutputBuffer();
	    return;
	}
	OnTalk(this, game);
}



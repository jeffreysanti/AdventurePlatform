#include "object.h"
#include "room.h"
#include "textgame.h"
#include "player.h"

Object::Object(TextAdventureGame *g, QString name, ObjScope scope, int lev, int x, int y)
{
	game = g;
	type = OBJ_NORMAL;
	if(scope == OS_GLOBAL || scope == OS_LOCAL)
	{
	    sTakeText = "You pick it up.";
	    sDropText = "You put it down.";
	}
	else if(scope == OS_STATIC || scope == OS_PLAYER)
	{
	    sTakeText = "You cannot take that.";
	    sDropText = "You cannot put that down.";
	}
	weight = 0;
	sUseText = "You Cannot Use That!";
	sLookDescription = "";
	OnLookAt = NULL;
	OnUse = NULL;
	OnTake = NULL;
	OnDrop = NULL;
	sName = name;
	s = scope;
	_lid = lev;
	_rx = x;
	_ry = y;
	// origs
	_orx = _rx;
	_ory = _ry;
	_olid = _lid;
}

Object::~Object()
{

}

QString Object::GetFullName()
{
    return sName;
}

void Object::Look()
{
    if(sLookDescription != "")
    {
	game->textbuffer->AddText(game->textbuffer->Center(GetDisplayName()) + "\n\n" + sLookDescription);
	game->textbuffer->OutputBuffer();
    }

    if(OnLookAt != NULL)
	OnLookAt(this, game);
}

void Object::Use()
{
	if(sUseText != "")
	{
		game->textbuffer->AddText(sUseText + "\n\n");
		game->textbuffer->OutputBuffer();
	}

	if(OnUse != NULL)
		OnUse(this, game);
}

void Object::Take()
{
    if(game->player->iMaxWeight > 0 && game->player->iWeight + weight > game->player->iMaxWeight)
    {
	game->textbuffer->AddText("This item weighs " + game->textbuffer->Int(weight));
	game->textbuffer->AddText(" units. You do not have enough room.\n");
	game->textbuffer->OutputBuffer();
	return;
    }
    if(sTakeText != "")
    {
	game->textbuffer->AddText(sTakeText + "\n\n");
	game->textbuffer->OutputBuffer();
    }

    // take object
    if(s == OS_GLOBAL || s == OS_LOCAL)
    {
	game->om->TakeObject(GetDisplayName(), _lid, _rx, _ry);

    	if(OnTake != NULL)
	    OnTake(this, game);
    }
}

void Object::Drop()
{
    if(sDropText != "")
    {
	game->textbuffer->AddText(sDropText + "\n\n");
	game->textbuffer->OutputBuffer();
    }

    // remove object
    if(s == OS_GLOBAL || s == OS_LOCAL)
    {
	game->om->DropObject(GetDisplayName(), game->player->GetCurrentLevelId(), game->player->GetCurrentRoom()->GetX(),
			  game->player->GetCurrentRoom()->GetY());

	if(OnDrop != NULL)
	    OnDrop(this, game);
    }
}

QString Object::GetDisplayName()
{
    if(StrContains(sName, ":"))
    {
	return sName.left(sName.indexOf(":"));
    }
    else
	return sName;
}

bool Object::IsAName(QString name)
{
    if(StrContains(sName, ":"))
    {
	if(game->textbuffer->Lower(name) == game->textbuffer->Lower(GetDisplayName()))
	    return true;
	if(game->textbuffer->Lower(sName).indexOf(":"+game->textbuffer->Lower(name)) > -1)
	    return true;
	return false;
    }
    else
    {
	if(game->textbuffer->Lower(name) == game->textbuffer->Lower(sName))
	    return true;
	else
	    return false;
    }
}

QList<QString> Object::GetAllNames()
{
    QString tmp = game->textbuffer->Lower(sName);
    QString s;
    QList<QString> L;
    while(tmp != "")
    {
	if(tmp.indexOf(":") > -1)
	{
	    s = tmp.left(tmp.indexOf(":"));
	    tmp = StrReplace(tmp, s+":", "");
	    L.push_back(s);
	}
	else
	{
	    L.push_back(tmp);
	    break;
	}
    }
    return L;
}

/*
void Object::Save(wfstream &f)
{
	write_word(f, objI); // unique object identifier

	write_word(f, sName.length());
	f.write(sName.c_str(), sName.length()*sizeof(char));

	write_word(f, sTakeText.length());
	f.write(sTakeText.c_str(), sTakeText.length()*sizeof(char));

	write_word(f, sDropText.length());
	f.write(sDropText.c_str(), sDropText.length()*sizeof(char));

	write_word(f, sLookDescription.length());
	f.write(sLookDescription.c_str(), sLookDescription.length()*sizeof(char));

	write_word(f, sUseText.length());
	f.write(sUseText.c_str(), sUseText.length()*sizeof(char));

	write_word(f, weight);
	write_word(f, (int)type);

}

void Object::Open(wfstream &f)
{
	read_word(f, objI); // unique object identifier

	sName = read_str(f);
	sTakeText = read_str(f);
	sDropText = read_str(f);
	sLookDescription = read_str(f);
	sUseText = read_str(f);

	read_word(f, weight);
	read_word(f, (int&)type);
}
*/

ObjScope Object::GetScope()
{
    return s;
}


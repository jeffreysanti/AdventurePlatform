#include "room.h"
#include "textgame.h"
#include "player.h"

Room::Room(TextAdventureGame *g, int x, int y, int num, QString name, int lev)
{
	game = g;
	iX = x;
	iY = y;
	iRoomNumber = num;
	rEast = rWest = rSouth = rNorth = NULL;
	sRoomName = name;
	iLevNumber = lev;
	playlistNme = "";
	OnEnterRoom = NULL;
	OnExitRoom = NULL;
}

Room::~Room()
{
	/*for(std::vector<Object*>::iterator it=O.begin(); it!=O.end(); it++)
	{
		if((*it)->type == OBJ_BOOK)
		{
			delete ((BookObject*)(*it));
			continue;
		}
		delete (*it);
	}
	O.clear();*/
}

int Room::GetX()
{
	return iX;
}
int Room::GetY()
{
	return iY;
}

int Room::GetLevelId()
{
    return iLevNumber;
}

void Room::Look()
{
	game->textbuffer->AddText(game->textbuffer->Center(sRoomName) + "\n\n");
	game->textbuffer->AddText(sDescription+"\n\n");
	game->textbuffer->AddText("Directions:\n");
	game->textbuffer->AddText("-----------\n");
	if(rEast != NULL)  game->textbuffer->AddText(" East\n");
	if(rWest != NULL)  game->textbuffer->AddText(" West\n");
	if(rNorth != NULL) game->textbuffer->AddText(" North\n");
	if(rSouth != NULL) game->textbuffer->AddText(" South\n");

	game->textbuffer->AddText("\nObjects:\n");
	game->textbuffer->AddText("--------\n");

	QList<Object*> O = game->om->GetList(iLevNumber, iX, iY);
	if(O.size() > 3)
	{
		int i=1;
		game->textbuffer->AddText(" ");
		for(QList<Object*>::iterator it=O.begin(); it!=O.end(); it++)
		{
			if(i % 3 == 0)
				game->textbuffer->AddText("\n ");
			game->textbuffer->AddText(game->textbuffer->Left((*it)->GetDisplayName(),
							     floor(double((game->textbuffer->TEXT_COLS-1) / 3))));
			i++;
		}
	}
	else
	{
		for(QList<Object*>::iterator it=O.begin(); it!=O.end(); it++)
		{
			game->textbuffer->AddText(" "+(*it)->GetDisplayName()+"\n");
		}
	}
}

Object *Room::NewObject(QString name, ObjScope s)
{
    Object *o = game->om->NewObject(name, s, iLevNumber, iX, iY);
    return o;
}

BookObject *Room::NewBookObject(QString name, ObjScope s)
{
    BookObject *o = game->om->NewBookObject(name, s, iLevNumber, iX, iY);
    return o;
}

CharacterObject *Room::NewCharacterObject(QString name, ObjScope s)
{
    CharacterObject *o = game->om->NewCharacterObject(name, s, iLevNumber, iX, iY);
    return o;
}
/*
Object *Room::FindObject(QString name)
{
	for(std::vector<Object*>::iterator it=O.begin(); it!=O.end(); it++)
	{
		if((*it)->IsAName(name))
		{
			return (*it);
		}
	}
	return NULL;
}

void Room::AddObject(Object *o)
{
	O.push_back(o);
}




Object *Room::RemoveObject(QString name)
{
	Object *o;
	for(std::vector<Object*>::iterator it=O.begin(); it!=O.end(); it++)
	{
		if((*it)->IsAName(name))
		{
			o = (*it);
			O.erase(it);
			return o;
		}
	}
	return NULL;
}*/

void Room::Save(QDataStream &out)
{
    out << iX;
    out << iY;
    int rooms = 0;
    if(rEast) rooms = rooms | EAST;
    if(rWest) rooms = rooms | WEST;
    if(rSouth) rooms = rooms | SOUTH;
    if(rNorth) rooms = rooms | NORTH;
    out << rooms;
}
/*
void Room::RemoveAllObjs(vector<Object*>&VO)
{
	for(vector<Object*>::iterator it=O.begin(); it!=O.end(); it++)
	{
		VO.push_back((*it));
	}
	O.clear();
}
*/

void Room::AddAmbientMusic(QString path)
{
    if(playlistNme == "")
    {
	playlistNme = "RoomAmbient"+sRoomName+QString::number(iX)+QString::number(iY)+QString::number(iLevNumber);
	game->am->CreatePlaylist(playlistNme);
    }
    game->am->LoadAudio(path, ST_AMBIENT);
    game->am->AddToPlaylist(playlistNme, path);
}

bool Room::StartAmbient() // false means there is no room ambience, so we shall continue level one
{
    if(playlistNme == "")
	return false;

    game->am->StartPlaylist(playlistNme);
    return true;
}

bool Room::EndAmbient()
{
    if(playlistNme == "")
	return false;

    game->am->StopPlaylist(playlistNme);
    return true;
}




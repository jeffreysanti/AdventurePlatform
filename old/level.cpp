#include "level.h"

#include "textgame.h"
#include "player.h"

Level::Level(TextAdventureGame *g, int num, QString name)
{
	game = g;
	iLevelNumber = num;
	startX = startY = 0;
	OnApplyRules = NULL;
	sLevelName = name;
	OnSave = NULL;
	OnLoad = NULL;
	playlistNme = "";

	OnEnterLevel = NULL;
	OnExitLevel = NULL;
}

Level::~Level()
{
	for(std::vector<Room*>::iterator it=R.begin(); it!=R.end(); it++)
	{
		delete (*it);
	}
	R.clear();
}

Room *Level::AddRoom(int x, int y, QString name)
{
	Room *r = new Room(game, x, y, R.size()+1, name, iLevelNumber);
	R.push_back(r);
	return r;
}

void Level::OpenAllDoors()
{
	int x, y;
	for(std::vector<Room*>::iterator it=R.begin(); it!=R.end(); it++)
	{
		x = (*it)->GetX();
		y = (*it)->GetY();
		(*it)->rEast = GetRoom(x+1, y);
		(*it)->rWest = GetRoom(x-1, y);
		(*it)->rNorth = GetRoom(x, y-1);
		(*it)->rSouth = GetRoom(x, y+1);
	}
}

void Level::OpenDoors(int rx, int ry, int ds)
{
	Room *r = GetRoom(rx, ry);
	Room *r2 = NULL;
	if(r == NULL)
		return;
	if(ds & NORTH)
	{
		r2 = GetRoom(rx, ry-1);
		r->rNorth = r2;
		if(r2 != NULL)
		{
			r2->rSouth = r;
		}
	}
	if(ds & SOUTH)
	{
		r2 = GetRoom(rx, ry+1);
		r->rSouth = r2;
		if(r2 != NULL)
		{
			r2->rNorth = r;
		}
	}
	if(ds & WEST)
	{
		r2 = GetRoom(rx-1, ry);
		r->rWest = r2;
		if(r2 != NULL)
		{
			r2->rEast = r;
		}
	}
	if(ds & EAST)
	{
		r2 = GetRoom(rx+1, ry);
		r->rEast = r2;
		if(r2 != NULL)
		{
			r2->rWest = r;
		}
	}
}

void Level::CloseDoors(int rx, int ry, int ds)
{
	Room *r = GetRoom(rx, ry);
	Room *r2 = NULL;
	if(r == NULL)
		return;
	if(ds & NORTH)
	{
		r2 = GetRoom(rx, ry-1);
		r->rNorth = NULL;
		if(r2 != NULL)
		{
			r2->rSouth = NULL;
		}
	}
	if(ds & SOUTH)
	{
		r2 = GetRoom(rx, ry+1);
		r->rSouth = NULL;
		if(r2 != NULL)
		{
			r2->rNorth = NULL;
		}
	}
	if(ds & WEST)
	{
		r2 = GetRoom(rx-1, ry);
		r->rWest = NULL;
		if(r2 != NULL)
		{
			r2->rEast = NULL;
		}
	}
	if(ds & EAST)
	{
		r2 = GetRoom(rx+1, ry);
		r->rEast = NULL;
		if(r2 != NULL)
		{
			r2->rWest = NULL;
		}
	}
}

void Level::CloseAllDoors()
{
	for(std::vector<Room*>::iterator it=R.begin(); it!=R.end(); it++)
	{
		(*it)->rEast = NULL;
		(*it)->rWest = NULL;
		(*it)->rNorth = NULL;
		(*it)->rSouth = NULL;
	}
}

Room *Level::GetRoom(int x, int y)
{
	for(std::vector<Room*>::iterator it=R.begin(); it!=R.end(); it++)
	{
		if((*it)->GetX() == x && (*it)->GetY() == y)
			return (*it);
	}
	return NULL;
}
Room *Level::GetRoom(QString name)
{
	for(std::vector<Room*>::iterator it=R.begin(); it!=R.end(); it++)
	{
		if(TextBuffer::Lower((*it)->sRoomName) == TextBuffer::Lower(name))
			return (*it);
	}
	return NULL;
}

void Level::Look()
{
	game->player->GetCurrentRoom()->Look();
}

int Level::GetId()
{
    return iLevelNumber;
}

/*void Level::RemoveAllObjs(vector<Object*>&VO)
{
	for(vector<Room*>::iterator it=R.begin(); it!=R.end(); it++)
	{
		(*it)->RemoveAllObjs(VO);
	}
}
*/
void Level::Save(QDataStream &out)
{
    // tell which doors are opened
    out << TextBuffer::Lower(sLevelName);
    out << (unsigned int)R.size();
    for(int i=0; i<(int)R.size(); i++)
    {
	R[i]->Save(out);
    }
    if(OnSave != NULL)
	OnSave(out, this, game);
}

void Level::Load(QDataStream &in)
{
    CloseAllDoors();
    int rms = 0;
    int x,y;
    in >> rms;
    for(int i=0; i<rms; i++)
    {
	in >> x;
	in >> y;
	Room *r = GetRoom(x,y);
	int rooms = 0;
	in >> rooms;
	if(r == NULL)
	    continue; // room no longer exists
	if(rooms & NORTH) r->rNorth = GetRoom(x, y-1);
	if(rooms & SOUTH) r->rSouth = GetRoom(x, y+1);
	if(rooms & EAST) r->rEast = GetRoom(x+1, y);
	if(rooms & WEST) r->rWest = GetRoom(x-1, y);
    }
    if(OnLoad != NULL)
	OnLoad(in, this, game);
}

void Level::AddAmbientMusic(QString path)
{
    if(playlistNme == "")
    {
	playlistNme = "LevelAmbient"+sLevelName+QString::number(iLevelNumber);
	game->am->CreatePlaylist(playlistNme);
    }
    game->am->LoadAudio(path, ST_AMBIENT);
    game->am->AddToPlaylist(playlistNme, path);
}

bool Level::StartAmbient() // false means there is no room ambience, so we shall continue level one
{
    if(playlistNme == "")
	return false;

    game->am->StartPlaylist(playlistNme);
    return true;
}

bool Level::PauseAmbient(bool pause)
{
    if(playlistNme == "")
	return false;

    game->am->SetPlaylistPause(playlistNme, pause);
    return true;
}

bool Level::EndAmbient()
{
    if(playlistNme == "")
	return false;

    game->am->StopPlaylist(playlistNme);
    return true;
}


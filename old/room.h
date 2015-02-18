#include "stdafx.h"
#include "objectmangager.h"
#include "audiomanager.h"

#ifndef ROOMH
#define ROOMH

const int WEST = 1;
const int EAST = 2;
const int NORTH = 4;
const int SOUTH = 8;

class Room
{
public:
	Room(TextAdventureGame *g, int x, int y, int num, QString name, int lev);
	~Room();

	QString sRoomName, sDescription;

	Room *rEast;
	Room *rWest;
	Room *rNorth;
	Room *rSouth;

	int GetX();
	int GetY();

	int GetLevelId();

	void Look();

	Object          *NewObject(QString name, ObjScope s = OS_STATIC);
	BookObject      *NewBookObject(QString name, ObjScope s = OS_STATIC);
	CharacterObject *NewCharacterObject(QString name, ObjScope s = OS_STATIC);

	void AddAmbientMusic(QString path);
	bool StartAmbient();
	bool EndAmbient();

	/*Object *FindObject(QString name);
	void AddObject(Object *o);
	Object *RemoveObject(QString name);*/

	void (*OnEnterRoom)(TextAdventureGame*);
	void (*OnExitRoom)(TextAdventureGame*);

	//void RemoveAllObjs(std::vector<Object*>&VO);
	void Save(QDataStream &out);

private:
	int iRoomNumber, iX, iY, iLevNumber;

	TextAdventureGame *game;

	QString playlistNme;

	//std::vector<Object*> O;
};

#endif

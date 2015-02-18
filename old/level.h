#include "stdafx.h"
#include "room.h"

#ifndef LEVELH
#define LEVELH

class TextAdventureGame;

class Level
{
public:
	Level(TextAdventureGame *g, int num, QString name);
	~Level();

	void Look();

	Room *AddRoom(int x, int y, QString name="");

	Room *GetRoom(int x, int y);
	Room *GetRoom(QString name);

	void OpenAllDoors();
	void CloseAllDoors();

	void OpenDoors(int rx, int ry, int ds);
	void CloseDoors(int rx, int ry, int ds);

	QString sLevelName, sLevelIntro;
	int startX, startY;

	void (*OnApplyRules)(TextAdventureGame*);

	void (*OnEnterLevel)(TextAdventureGame*);
	void (*OnExitLevel)(TextAdventureGame*);

	int GetId();

	//void RemoveAllObjs(std::vector<Object*>&VO);
	void Save(QDataStream &out);
	void Load(QDataStream &in);

	void (*OnSave)(QDataStream &, Level*, TextAdventureGame*);
	void (*OnLoad)(QDataStream &, Level*, TextAdventureGame*);

	void AddAmbientMusic(QString path);
	bool PauseAmbient(bool pause);
	bool StartAmbient();
	bool EndAmbient();

private:
	TextAdventureGame *game;
	int iLevelNumber;

	std::vector<Room*> R;
	QString playlistNme;
};

#endif


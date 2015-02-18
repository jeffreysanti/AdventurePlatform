#include "stdafx.h"
#include "textbuffer.h"
#include "drawer.h"
#include "audiomanager.h"
#include "room.h"
#include "objectmangager.h"
#include "level.h"

#ifndef PLAYERH
#define PLAYERH

class TextAdventureGame;


class Player // Using this very class any aspect of the game can be changed in any of the callback functions so Have Fun :P
{
public:
	Player(TextAdventureGame *g);
	~Player();

	int iMaxWeight; // 0: infinite
	int iWeight;
	void CalculateWeight();

	void EndGame(bool good, QString message);
	void ShowDialog(QString text);
	void GotoLevel(int lev);
	void GotoLevel(QString lev);

	void ShowInventory();

	/*
	void AddObject(Object *o);
	Object *FindObject(QString name);
	Object *RemoveObject(QString name);
*/

	Object          *NewObject(QString name, ObjScope s = OS_STATIC);
	BookObject      *NewBookObject(QString name, ObjScope s = OS_STATIC);
	CharacterObject *NewCharacterObject(QString name, ObjScope s = OS_STATIC);

	QString sName;

	Level *GetCurrentLevel();
	int GetCurrentLevelId();
	Room  *GetCurrentRoom();

	bool ended;
	bool chLevel;

	//void RemoveAllObjs(vector<Object*>&VO);
	void Save(QDataStream &out);
	void Load(QDataStream &in);

	//int objIdentifier; // DO NOT TOUCH

	void _setLevel(Level *lev);
	void _setLevelId(int lid);
	void _setRoom(Room *rom);

private:
	//std::vector<Object*> O;
	TextAdventureGame *game;

	int LevelId;
	Level *l; // current level
	Room *r;
};

#endif

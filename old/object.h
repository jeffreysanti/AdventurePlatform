#include "stdafx.h"
#include "textbuffer.h"
#include "objectmangager.h"

#ifndef OBJH
#define OBJH

class TextAdventureGame;

enum ObjectType{
	OBJ_NORMAL,
	OBJ_BOOK,
	OBJ_CHARACTER
};

enum ObjScope{
    OS_LOCAL = 1, // level-specific -- disappears when level change
    OS_STATIC = 2, // non-movable
    OS_GLOBAL = 4, // movable anywhere
    OS_PLAYER = 8 // player has it & cannot drop
};

class Object
{
public:
	Object(TextAdventureGame *g, QString name, ObjScope scope, int lev, int x, int y);
	~Object();

	QString GetFullName();

	ObjectType type;

	int weight;
	QString sTakeText;
	QString sDropText;
	void (*OnTake)(Object*, TextAdventureGame*);
	void Take();
	void (*OnDrop)(Object*, TextAdventureGame*);
	void Drop();


	QString sLookDescription;
	void Look();
	void (*OnLookAt)(Object*, TextAdventureGame*);

	QString sUseText;
	void (*OnUse)(Object*, TextAdventureGame*);
	void Use();


	QString GetDisplayName();
	bool IsAName(QString name);

	QList<QString> GetAllNames();

	ObjScope GetScope();

	//void Save(wfstream &f);
	//void Open(wfstream &f);

	int _lid; // id of level (-1 if player)
	int _rx, _ry; // current room object is in

	// ne touche pas
	int _olid;
	int _orx, _ory;

protected:

	TextAdventureGame *game;
	ObjScope s;
	QString sName;

};


#endif

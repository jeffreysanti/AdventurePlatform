#include "object.h"

#ifndef CHAROH
#define CHAROH


struct DialogOpt{
	QString name;
	QString text;
};

class DialogOptions
{
public:
	DialogOptions(TextAdventureGame *g);
	~DialogOptions();

	void AddOption(QString name, QString text);
	void RemoveOption(QString name);

	QString ShowOptions();


private:
	std::vector<DialogOpt> O;
	TextAdventureGame *game;

};

class CharacterObject : public Object
{
public:
	CharacterObject(TextAdventureGame *g, QString name, ObjScope scope, int lev, int x, int y);
	~CharacterObject();

	void Talk();
	void (*OnTalk)(Object*, TextAdventureGame*);

private:

};

#endif

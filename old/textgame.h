#include "stdafx.h"

class AudioManager;
class Player;
class ObjectManager;
class Level;
class Room;
class Drawer;
class TextBuffer;

class MainWindow;

class TextAdventureGame
{
public:
	TextAdventureGame(MainWindow *w, void (*loadFunc)(TextAdventureGame*), QString name, QString intro);
	~TextAdventureGame();

	void BeginGame();

	Level *AddLevel(QString name="");

	void MessageLoop(int &code);

	void Save(QString fname);
	void Load(QString fname);

	Level *GetLevel(int id);
	Level *GetLevel(QString name);

	void (*OnSave)(QDataStream &, TextAdventureGame*);
	void (*OnLoad)(QDataStream &, TextAdventureGame*);

	void (*OnLoadLevels)(TextAdventureGame*);

	Player *player;
	TextBuffer *textbuffer;
	ObjectManager *om;
	AudioManager *am;
	MainWindow *win;

private:
	void StartNewLevel();
	bool LoadSavedGame();
	bool SaveGame();

	void UpdateAudio();
	Level *oALev;
	Room  *oARoom;

	int ShowMenu(int status);
	void StartNewGame();

	QString sName, sIntro;


	QList<Level*> L;
};

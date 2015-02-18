#include "object.h"

#ifndef BOOKOH
#define BOOKOH

class Page
{
public:
	Page(TextAdventureGame *g, int n);
	Page(Page *p);
	~Page();

	void AddParagraph(QString text);
	void DrawPage();

	int num;

	//void Save(wfstream &f);
	//void Load(wfstream &f);
private:
	std::vector<QString> S;
	TextAdventureGame *game;

};

class BookObject : public Object
{
public:
	BookObject(TextAdventureGame *g, QString name, ObjScope scope, int lev, int x, int y);
	~BookObject();

	Page *AddPage();
	Page *AddPage(Page * pg);
	void Read();
	int curPage;

	Page *GetPage(int num);

	//void BookSave(wfstream &f);
	//void BookLoad(wfstream &f);

private:
	std::vector<Page*> P;
};

#endif


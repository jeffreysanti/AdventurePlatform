#include "bookobject.h"
#include "textgame.h"

Page::Page(TextAdventureGame *g, int n)
{
	num = n;
	game = g;
}

Page::Page(Page *p)
{
	if(p == NULL)
	{
		num = -1;
	}
	else
	{
		num = p->num;
		for(int i=0; i<(int)p->S.size(); i++)
		{
			S.push_back(p->S[i]);
		}
		game = p->game;
	}
}

Page::~Page()
{
	S.clear();
}

void Page::AddParagraph(QString text)
{
	S.push_back(text);
}

void Page::DrawPage()
{
	for(std::vector<QString>::iterator it=S.begin(); it!=S.end(); it++)
	{
	    game->textbuffer->AddText((*it) + "\n");
	}
}

/*void Page::Save(wfstream &f)
{
	write_word(f, num);
	write_word(f, S.size());
	for(int i=0; i<S.size(); i++)
	{
		write_word(f, S[i].length());
		f.write(S[i].c_str(), S[i].size()*sizeof(char));
	}
}

void Page::Load(wfstream &f)
{
	read_word(f, num);
	int sz;
	read_word(f, sz);
	for(int i=0; i<sz; i++)
	{
		S.push_back(read_str(f));
	}
}
*/

BookObject::BookObject(TextAdventureGame *g, QString name, ObjScope scope, int lev, int x, int y)
	    : Object(g, name, scope, lev, x, y)
{
	type = OBJ_BOOK;
	curPage = 1;
}

BookObject::~BookObject()
{
	for(std::vector<Page*>::iterator it=P.begin(); it!=P.end(); it++)
	{
		delete (*it);
	}
	P.clear();
}

Page *BookObject::AddPage()
{
	Page *p = new Page(game, P.size());
	P.push_back(p);
	return p;
}

Page *BookObject::AddPage(Page *pg)
{
	P.push_back(pg);
	return pg;
}

void BookObject::Read()
{
	if(curPage > (int)P.size())
	{
		game->textbuffer->AddText(game->textbuffer->Center("Book Empty"));
		game->textbuffer->AddText("\n\n");
		game->textbuffer->OutputBuffer();
		return;
	}
	QString ln;
	Page *p;
	while(true)
	{
		p = P[curPage-1];
		game->textbuffer->AddText("Page " + game->textbuffer->Int(curPage) + " / " + game->textbuffer->Int(P.size()) + "\n\n");
		p->DrawPage();
		game->textbuffer->AddText("\n\n" + game->textbuffer->Center("[Next Or Back(n or b)]"));
		game->textbuffer->OutputBuffer(false);
		ln = game->textbuffer->GetLine();
		if(game->textbuffer->bQuit)
		{
		    return;
		}
		if(game->textbuffer->Lower(ln) == "quit" || game->textbuffer->Lower(ln) == "q")
			return;
		else if(game->textbuffer->Lower(ln) == "next" || game->textbuffer->Lower(ln) == "n")
		{
			curPage ++;
			if(curPage > (int)P.size())
				curPage --;
		}
		else if(game->textbuffer->Lower(ln) == "back" || game->textbuffer->Lower(ln) == "b")
		{
			curPage --;
			if(curPage < 1)
				curPage ++;
		}
	}
}

/*void BookObject::BookSave(wfstream &f)
{
	write_word(f, P.size());
	for(int i=0; i<P.size(); i++)
	{
		P[i]->Save(f);
	}
}

void BookObject::BookLoad(wfstream &f)
{
	for(int i=0; i<P.size(); i++)
	{
		delete  P[i];
	}
	P.clear();
	int sz;
	read_word(f, sz);
	for(int i=0; i<sz; i++)
	{
		Page *p = new Page(i);
		p->Load(f);
		P.push_back(p);
	}
}
*/

Page *BookObject::GetPage(int num)
{
	if(num > (int)P.size() || num < 1)
	{
		return NULL;
	}
	return P[num-1];
}


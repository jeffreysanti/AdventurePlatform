#include "player.h"
#include "textgame.h"



Player::Player(TextAdventureGame *g)
{
	sName = "UNAMED";
	ended = false;
	iMaxWeight = 0;
	chLevel = false;
	game = g;
	iWeight = 0;
	//objIdentifier = 0;
	LevelId = -1;
	r = NULL;
	l = NULL;
}

Player::~Player()
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


void Player::GotoLevel(int lev)
{
	LevelId = lev;
	chLevel = true;
}

void Player::GotoLevel(QString lev)
{
	if(game->GetLevel(lev) != NULL)
	{
	    LevelId = game->GetLevel(lev)->GetId();
	    chLevel = true;
	}
	else
	{
	    LevelId = 9999999; // hopefully no such level exists
	    chLevel = true; // give error anyway
	}
}

void Player::EndGame(bool good, QString message)
{
	if(good)
	{
		game->textbuffer->AddText(game->textbuffer->Center("--Congratulations--") + "\n\n\n");
	}
	else
	{
		game->textbuffer->AddText(game->textbuffer->Center("--Game Over--") + "\n\n\n");
	}
	game->textbuffer->AddText(message);
	game->textbuffer->OutputBuffer();
	ended = true;
}

Object *Player::NewObject(QString name, ObjScope s)
{
    Object *o = game->om->NewObject(name, s, -1, 0, 0);
    return o;
}

BookObject *Player::NewBookObject(QString name, ObjScope s)
{
    BookObject *o = game->om->NewBookObject(name, s, -1, 0, 0);
    return o;
}

CharacterObject *Player::NewCharacterObject(QString name, ObjScope s)
{
    CharacterObject *o = game->om->NewCharacterObject(name, s, -1, 0, 0);
    return o;
}

/*

Object *Player::FindObject(QString name)
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

void Player::AddObject(Object *o)
{
	O.push_back(o);
	CalculateWeight();
}


Object *Player::RemoveObject(QString name)
{
	Object *o;
	for(std::vector<Object*>::iterator it=O.begin(); it!=O.end(); it++)
	{
		if((*it)->IsAName(name))
		{
			o = (*it);
			O.erase(it);
			CalculateWeight();
			return o;
		}
	}
	return NULL;
}
*/
void Player::CalculateWeight()
{
    iWeight = 0;
    QList<Object*> O = game->om->GetList(-1, 0, 0);
    for(QList<Object*>::iterator it=O.begin(); it!=O.end(); it++)
    {
	iWeight += (*it)->weight;
    }
}

void Player::ShowInventory()
{
	game->textbuffer->AddText(game->textbuffer->Center("Inventory") + "\n\n");
	QList<Object*> O = game->om->GetList(-1, 0, 0);
	for(QList<Object*>::iterator it=O.begin(); it!=O.end(); it++)
	{
	    game->textbuffer->AddText(game->textbuffer->Left((*it)->GetDisplayName(), 30) + "  Weight: " +
				game->textbuffer->Int((*it)->weight) + "\n");
	}
	game->textbuffer->AddText("\nUsed: " + game->textbuffer->Int(iWeight));
	if(iMaxWeight > 0)
		game->textbuffer->AddText(" / " + game->textbuffer->Int(iMaxWeight) + "\n");

	game->textbuffer->OutputBuffer();
	return;
}

void Player::Save(QDataStream &out)
{
    out << sName;
    out << iWeight;
    out << LevelId;
    out << r->GetX();
    out << r->GetY();
}

void Player::Load(QDataStream &in)
{
    in >> sName;
    in >> iWeight;
    in >> LevelId;
    int x,y;
    in >> x;
    in >> y;
    l = game->GetLevel(LevelId);
    r = l->GetRoom(x, y);
}

/*
void Player::RemoveAllObjs(vector<Object*>&VO)
{
	for(vector<Object*>::iterator it=O.begin(); it!=O.end(); it++)
	{
		VO.push_back((*it));
	}
	O.clear();
}

void Player::Load(wfstream &f, vector<Object*>&VO)
{
	sName = read_str(f);
	read_word(f, iWeight);
	read_word(f, LevelId);
	int sz = 0;
	read_word(f, sz);
	for(int i=0; i<sz; i++)
	{
		Object o(this);
		o.Open(f);
		for(vector<Object*>::iterator it=VO.begin(); it!=VO.end(); it++)
		{
			if((*it)->GetObjI() == o.GetObjI())
			{
				// cpy object parts
				(*it)->sDropText = o.sDropText;
				(*it)->sLookDescription = o.sLookDescription;
				(*it)->sName = o.sName;
				(*it)->sTakeText = o.sTakeText;
				(*it)->sUseText = o.sUseText;
				(*it)->weight = o.weight;
				if((*it)->type == OBJ_BOOK)
				{
					((BookObject*)(*it))->BookLoad(f); // it will do cpying
				}
				AddObject((*it));
			}
		}
	}
	int x,y;
	read_word(f, x);
	read_word(f, y);
	r = game->GetLevel(LevelId)->GetRoom(x, y);
}
*/

Level *Player::GetCurrentLevel()
{
    return l;
}

int Player::GetCurrentLevelId()
{
    return LevelId;
}

Room *Player::GetCurrentRoom()
{
    return r;
}

void Player::_setLevel(Level *lev)
{
    l = lev;
}

void Player::_setLevelId(int lid)
{
    LevelId = lid;
}

void Player::_setRoom(Room *rom)
{
    r = rom;
}


void Player::ShowDialog(QString text)
{
	game->textbuffer->AddText(text + "\n\n");
	game->textbuffer->OutputBuffer();
}


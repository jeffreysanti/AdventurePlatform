#include "objectmangager.h"
#include "textgame.h"
#include "player.h"

ObjectManager::ObjectManager(TextAdventureGame *g)
{
    game = g;
}

ObjectManager::~ObjectManager()
{
    for(QList<Object*>::iterator it=O.begin(); it!=O.end(); it++)
    {
	if((*it)->type == OBJ_BOOK)
	{
	    delete ((BookObject*)(*it));
	    continue;
	}
	delete (*it);
    }
    O.clear();
}


Object *ObjectManager::NewObject(QString name, ObjScope s, int lid, int x, int y)
{
    if(s == OS_PLAYER)
    {
	lid = -1;
	x = y = 0;
    }
    Object *o = new Object(game, name, s, lid, x, y);
    O.push_back(o);
    //QMessageBox::information(0, "Information", "Information message text");
    return o;
}

BookObject *ObjectManager::NewBookObject(QString name, ObjScope s, int lid, int x, int y)
{
    if(s == OS_PLAYER)
    {
	lid = -1;
	x = y = 0;
    }
    BookObject *o = new BookObject(game, name, s, lid, x, y);
    O.push_back(o);
    //QMessageBox::information(0, "Information", "Information message text");
    return o;
}

CharacterObject *ObjectManager::NewCharacterObject(QString name, ObjScope s, int lid, int x, int y)
{
    if(s == OS_PLAYER)
    {
	lid = -1;
	x = y = 0;
    }
    CharacterObject *o = new CharacterObject(game, name, s, lid, x, y);
    O.push_back(o);
    //QMessageBox::information(0, "Information", "Information message text");
    return o;
}

QList<Object*> ObjectManager::GetList(int lev, int x, int y)
{
    QList<Object*> ro;
    for(int i=0; i<O.size(); i++)
    {
	if((lev == -1 && O[i]->_lid == -1) ||
	    (O[i]->_lid == lev && O[i]->_rx == x && O[i]->_ry == y))
	{
	    ro.push_back(O[i]);
	}
    }
    return ro;
}

Object *ObjectManager::GetObject(QString name, int lid, int x, int y, bool inven)
{
    if(lid == -1)
    {
	inven = true;
    }
    for(int i=0; i<O.size(); i++)
    {
	if((inven && O[i]->_lid == -1 && O[i]->IsAName(name)) ||
	    (O[i]->_lid == lid && O[i]->_rx == x && O[i]->_ry == y && O[i]->IsAName(name)))
	{
	    return O[i];
	}
    }
    return NULL;
}

void ObjectManager::TakeObject(QString name, int lid, int x, int y)
{
    for(int i=0; i<O.size(); i++)
    {
	if(O[i]->_lid == lid && O[i]->_rx == x && O[i]->_ry == y && O[i]->IsAName(name)) // found object
	{
	    // confirm
	    if(O[i]->GetScope() == OS_LOCAL || O[i]->GetScope() == OS_GLOBAL)
	    {
		O[i]->_lid = -1;
		O[i]->_rx = O[i]->_ry = 0;
		game->player->CalculateWeight();
		return;
	    }
	    else
	    {
		QMessageBox::warning(0, "Error", "Take Type failed");
	    }
	}
    }
}

void ObjectManager::DropObject(QString name, int lid, int x, int y)
{
    for(int i=0; i<O.size(); i++)
    {
	if(O[i]->_lid == -1 && O[i]->IsAName(name)) // found object
	{
	    // confirm
	    if(O[i]->GetScope() == OS_LOCAL || O[i]->GetScope() == OS_GLOBAL)
	    {
		O[i]->_lid = lid;
		O[i]->_rx = x;
		O[i]->_ry = y;
		game->player->CalculateWeight();
		return;
	    }
	    else
	    {
		QMessageBox::warning(0, "Error", "Drop Type failed");
	    }
	}
    }
}

void ObjectManager::ChangeLevel(int lid, int ox, int oy)
{
    QList<Object*>L = GetList(-1, 0, 0);
    for(int i=0; i<L.size(); i++)
    {
	if(L[i]->GetScope() == OS_LOCAL && L[i]->_olid != lid)
	{
	    L[i]->_lid = L[i]->_olid;
	    L[i]->_rx = ox;
	    L[i]->_ry = oy;
	}
    }
}

void ObjectManager::CheckForWarnings()
{
    bool show = false;
    Object *o, *o2;
    QList<QString> n, n2;
    QString s, s2;
    for(int i=0; i<O.size(); i++)
    {
	o = O[i];
	if(o->GetFullName().indexOf("::") > -1)
	{
	    game->textbuffer->AddText("WARNING: Format of["+o->GetFullName()+"]\n");
	    show = true;
	}
	n = o->GetAllNames();
	for(int i2=0; i2<O.size(); i2++)
	{
	    if(i2 == i)
		continue;
	    o2 = O[i2];
	    if((o->GetScope() == OS_GLOBAL) ||
	       (o->GetScope() == OS_LOCAL && o->_lid == o2->_lid) ||
	       (o->GetScope() == OS_STATIC && o->_lid == o2->_lid
		    && o->_rx == o2->_rx && o->_ry == o2->_ry)   ||
	       (o->GetScope() == OS_PLAYER))
	    {
		n2 = o2->GetAllNames();
		for(int x=0; x<n.size(); x++)
		{
		    s = n[x];
		    for(int y=0; y<n2.size(); y++)
		    {
			s2 = n2[y];
			if(s == s2)
			{
			    game->textbuffer->AddText("WARNING: Object["+o->GetFullName()+"]{"+s+"}could"
						" interfere with["+o2->GetFullName()+"]{"+s2+"}\n");
			    show = true;
			}
		    }
		}
	    }
	}
    }
    if(show)
    {
	game->textbuffer->OutputBuffer(true);
    }
}

void ObjectManager::Save(QDataStream &out)
{
    QList<Object*>L;
    for(int i=0; i<O.size(); i++)
    {
	if((O[i]->GetScope() == OS_GLOBAL &&
	    (O[i]->_lid != O[i]->_olid || O[i]->_rx != O[i]->_orx || O[i]->_ry != O[i]->_ory)) ||
	   (O[i]->GetScope() == OS_LOCAL && (O[i]->_rx != O[i]->_orx || O[i]->_ry != O[i]->_ory)))
	{
	    L.push_front(O[i]);
	}
    }
    out << L.size();
    for(int i=0; i<L.size(); i++)
    {
	out << L[i]->GetScope();
	out << L[i]->_lid;
	out << game->textbuffer->Lower(L[i]->GetDisplayName());
	out << L[i]->_rx;
	out << L[i]->_ry;
    }
}

void ObjectManager::Load(QDataStream &in)
{
    int s;
    int num;
    QString name;
    int lid;
    Object *o = NULL;

    in >> num;
    for(int i=0; i<num; i++)
    {
	in >> s;
	in >> lid;
	in >> name;
	if(ObjScope(s) == OS_GLOBAL)
	{
	    for(int x=0; x<O.size(); x++)
	    {
		if(O[x]->GetScope() == OS_GLOBAL && game->textbuffer->Lower(O[x]->GetDisplayName()) == name)
		{
		    o = O[x];
		}
	    }
	}
	else
	{
	    for(int x=0; x<O.size(); x++)
	    {
		if(game->textbuffer->Lower(O[x]->GetDisplayName()) == name && O[x]->_lid == lid)
		{
		    o = O[x];
		}
	    }
	}
	o->_lid = lid;
	in >> o->_rx;
	in >> o->_ry;
    }
}





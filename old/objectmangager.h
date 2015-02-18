#ifndef OBJECTMANGAGER_H
#define OBJECTMANGAGER_H

#include "bookobject.h"
#include "characterobject.h"


class TextAdventureGame;

class ObjectManager
{
public:
    ObjectManager(TextAdventureGame *g);
    ~ObjectManager();

    Object *NewObject(QString name, ObjScope s, int lid, int x, int y);
    BookObject *NewBookObject(QString name, ObjScope s, int lid, int x, int y);
    CharacterObject *NewCharacterObject(QString name, ObjScope s, int lid, int x, int y);

    QList<Object*> GetList(int lev, int x, int y);

    Object *GetObject(QString name, int lid, int x, int y, bool inven);

    void TakeObject(QString name, int lid, int x, int y);
    void DropObject(QString name, int lid, int x, int y);

    void ChangeLevel(int lid, int ox, int oy);
    void CheckForWarnings();

    void Save(QDataStream &out);
    void Load(QDataStream &in);

private:
    QList<Object*> O;
    TextAdventureGame *game;
};

#endif // OBJECTMANGAGER_H

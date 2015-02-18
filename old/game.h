#ifndef GAME_H
#define GAME_H

#include "textgame.h"
#include "player.h"

struct World{
    QString name;
    QString desc;
    QString pwd; // "" = none; "*" = password, but no correct one (always locked)
    QString dComPwd;
};
struct Choice{
    int num;
    int pg;
    int wid;
};

extern QList<World> W;

QDataStream& operator<<(QDataStream& s, const World w);
QDataStream& operator>>(QDataStream& s, World &w);

// Level List

void ToKeVrTerminal(Object *, TextAdventureGame *);
void DeComTerminal(Object *, TextAdventureGame *);

// ------------ 1 KE'VR --------------
void Create_KeVr(TextAdventureGame *, Level *);
void Save_KeVr(QDataStream &, Level*, TextAdventureGame*);
void Load_KeVr(QDataStream &, Level*, TextAdventureGame*);

// ------------ 2 Dita Ba --------------
void Create_DitaBa(TextAdventureGame *, Level *);
void Save_DitaBa(QDataStream &, Level*, TextAdventureGame*);
void Load_DitaBa(QDataStream &, Level*, TextAdventureGame*);

// ------------ 2 Dita Ba --------------
void Create_Kengland(TextAdventureGame *, Level *);
void Save_Kengland(QDataStream &, Level*, TextAdventureGame*);
void Load_Kengland(QDataStream &, Level*, TextAdventureGame*);




#endif // GAME_H

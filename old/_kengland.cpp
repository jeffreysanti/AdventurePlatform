#include "game.h"


void Save_Kengland(QDataStream &out, Level *l, TextAdventureGame *game)
{

}

void Load_Kengland(QDataStream &in, Level *l, TextAdventureGame *game)
{

}

void OnLookStationList(Object *o, TextAdventureGame *game)
{
    game->textbuffer->AddText("<X2>"+game->textbuffer->Center("Departures/Arrivals", 60)+"\n");
    game->textbuffer->AddText("<XC>  CITY          DIR   TIME   TRAIN          PLAT   STATUS\n");
    game->textbuffer->AddText("<X2>  KLONDON       DPRT  21:34  ACLA T4545     34     ON-TIME\n");
    game->textbuffer->AddText("<X2>  KAMBRIDGE     ARIV  05:14  GAS SLOW E432  07     LATE\n");

    game->textbuffer->OutputBuffer();
}

void Create_Kengland(TextAdventureGame *game, Level *l)
{
    // add to Ke'Vr's world list
    World w;
    w.name = "Kengland";
    w.desc = "  Explore the lively streets of cities like\n"
	     "  Klondon, Kambridge, and Kristol under rule\n"
	     "  of the House of Norman.";
    w.dComPwd = "";
    W.push_back(w);

    // Lord Kodish - corrupt evil lord
    // What Would Kodish Do? WWKD



    // build the level
    Room  *r;
    Object *o;
    BookObject *bo;
    Page *pg;
    CharacterObject *co;
    Drawer d;
    Layer y;

    r = l->AddRoom(0,0, "New Konventry Station");
    r->sDescription = "This is the arrivals section of New Koventry Station, where people such as yourself travel"
		      " from Ke'Vr to experience Kengland's \"beauty.\" People quickly pass throught the terminals to"
		      " return to Ke'Vr. You can bearly hear yourself think in the herd of humans. The room is dimly"
		      " lit, and the concrete walls contain no windows. The main departure section is to the south";
    o = r->NewObject("Terminal:comuter:teleporter");
    o->sLookDescription = "The terminal takes you back to Ke'Vr.";
    o->sUseText = "";
    o->OnUse = &ToKeVrTerminal;

    r = l->AddRoom(0, 1, "New Koventry Station");
    r->sDescription = "You are in the departure section of the station. A large electronic bill board lists the arrivals"
		      " and departures throughout Kengland";
    o = r->NewObject("Billboard:sign:list");
    o->OnLookAt = &OnLookStationList;

    l->OpenAllDoors();
    l->sLevelIntro = "You fall into the busy New Koventry Station";
    l->startX = 0;
    l->startY = 0;
    l->OnLoad = &Load_Kengland;
    l->OnSave = &Load_Kengland;
}




#include "game.h"

QList<World> W; // external defenition

QDataStream& operator<<(QDataStream& s, const World w)
{
    s << w.name;
    s << w.desc;
    s << w.pwd;
    s << w.dComPwd;
    return s;
}

QDataStream& operator>>(QDataStream& s, World &w)
{
    s >> w.name;
    s >> w.desc;
    s >> w.pwd;
    s >> w.dComPwd;
    return s;
}

void LoadLvls(TextAdventureGame *game)
{
    Create_KeVr(game, game->AddLevel("Ke'vr"));
    Create_DitaBa(game, game->AddLevel("Dita Ba"));
    Create_Kengland(game, game->AddLevel("Kengland"));
}

void OnSaveGame(QDataStream &out, TextAdventureGame *g)
{

}

void OnLoadGame(QDataStream &in, TextAdventureGame *g)
{

}


bool GameMain(MainWindow *w)
{
    TextAdventureGame *game = new TextAdventureGame(w, &LoadLvls, "Ke'vr", "The cans need <XE>your<XX> help.");

    game->OnSave = &OnSaveGame;
    game->OnLoad = &OnLoadGame;

  /*  game->am->LoadAudio("audio/OverCoat__Memories_EP__1__Reflections_64kb.mp3", ST_AMBIENT);
    game->am->LoadAudio("audio/ercaMusSeg02-1.ogg", ST_AMBIENT);*/

    game->am->LoadAudio("audio/OverCoat__Memories_EP__4__Dreams_64kb.mp3", ST_STREAM_SOUND);
    game->am->SetLoop("audio/OverCoat__Memories_EP__4__Dreams_64kb.mp3", true);
    game->am->StartAudio("audio/OverCoat__Memories_EP__4__Dreams_64kb.mp3");

    game->BeginGame();

    game->am->StopAudio("audio/OverCoat__Memories_EP__4__Dreams_64kb.mp3");

    int code = 0;
    while(true)
    {
	game->MessageLoop(code);
	if(code == -1)
	    break;
    }

    //delete game;
    #ifdef _DEBUG
	    _CrtDumpMemoryLeaks();
    #endif

    return true;
}


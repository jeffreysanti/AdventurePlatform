#include "game.h"

QString deConCode;
QString storageCombo;

void OnTouchUranium(Object *o, TextAdventureGame *game)
{
    game->player->EndGame(false, "Under normal conditions, the uranium that your genius self decided to touch"
		    " would take days, months, or even years to harm you (if it does at all), but"
		    " for the purpouse of this game, let's just say it instantly killed you.\n\n"
		    "Victory For The Rock!\n<XE>"
"		    _.,--`_____`--.._\n"
"		 _,'                 `._\n"
"	       ,`                       ``.\n"
"	     ,`   ,`\\                /'.   `.\n"
"	   .    ,`...\\              /...`.   .\n"
"	  /   ,`......\\            /......`.  \\\n"
"	 ,   `, .......\\          /......,,'   `\n"
"	|      `., .....\\        /......'       |\n"
"      ,          `._ ...\\      /.....'          .\n"
"       |             `. . \\    /...,'            |\n"
"      ,                `.` ,--. '.`               .\n"
"      |                   ( .. )                  |\n"
"      '                    `--'                   '\n"
"       |                   .--.                  |\n"
"       `                   |..|                  '\n"
"	|                  |..|                 |\n"
"	 `                ......               ,\n"
"	  \\               |....|              /\n"
"	   `.            |......|           ,'\n"
"	     `.          |______|         ,'\n"
"	       `._                     _,'\n"
"		  `._               _,'\n"
"		     ``--._____.--''");
}

void OnTalkToMan(Object *o, TextAdventureGame *game)
{
    //CharacterObject *co = (CharacterObject*)o;
    game->player->ShowDialog("You: Hey, Sir. Are you okay?");
    game->player->ShowDialog("Man: Huuh. Ohh yeeah. I'm finnnne.");
    game->player->ShowDialog("You: You need to get out of Dita Ba, and get a doctor.");
    game->player->ShowDialog("Man: Buuut, my le-legs.");
    game->player->ShowDialog("You: I can carry you.");
}

void OnUseStorageKeyPad(Object *o, TextAdventureGame *game)
{
    if(game->player->GetCurrentLevel()->GetRoom(5, 3)->rSouth)
    {
	return; // already done
    }
    game->textbuffer->AddText("Please Enter Storage Unit Passkey:");
    game->textbuffer->OutputBuffer(false);
    QString in = game->textbuffer->GetLine();
    if(in == storageCombo)
    {
	game->textbuffer->AddText("Please Enter Storage Unit Passkey:\n\n");
	game->textbuffer->AddText("Access Granted");
	game->textbuffer->OutputBuffer(false);
	game->textbuffer->Wait(1000);
	game->player->GetCurrentLevel()->OpenDoors(5, 3, SOUTH);
	o->sUseText = "The door is already unlocked.";
	return;
    }
    else
    {
	game->textbuffer->AddText("Please Enter Storage Unit Passkey:\n\n");
	game->textbuffer->AddText("Access Denied");
	game->textbuffer->OutputBuffer(false);
	game->textbuffer->Wait(1000);
	return;
    }
}

void Save_DitaBa(QDataStream &out, Level *l, TextAdventureGame *game)
{
    out << deConCode;
    out << storageCombo;
}

void Load_DitaBa(QDataStream &in, Level *l, TextAdventureGame *game)
{
    in >> deConCode;
    in >> storageCombo;

    World w;
    for(int i=0; i<W.size(); i++)
    {
	if(game->textbuffer->Lower(W[i].name) == "dita ba")
	{
	    W[i].dComPwd = deConCode;
	    break;
	}
    }

    Object *o;
    o=game->om->GetObject("Shelf", l->GetId(), 2, -1, true);
    o->sLookDescription = "From a distance the shelf is an ordianry metal shelf with empty stacks of"
			  " BeanoRad anti-radiation drugs. After stepping closer you see printed on"
			  " the boxes:\n\n"
			  "HazHouse Emergency Supply Store\n"
			  "1485 Richard Sreet\n"
			  "Dita Ba, Dita Ba, Ke'Vr\n"
			  "{Storage: "+storageCombo+"}";
    o=game->om->GetObject("Note", l->GetId(), 5, 4, true);
    o->sLookDescription = "The note reads:\n\n"
			  "Dear Reader of This Note,\n\n"
			  "   If you have obtained this note, most likely Dita Ba is in major trouble"
			  " and is on its way to collapse. Once everyone is out of Dita Ba, please"
			  " go to Dita Ba's DeCom center and enter the code: \n" + deConCode;
}

void EnterHazHouse(TextAdventureGame *game)
{
    game->am->LoadAudio("audio/Airport Lounge.mp3", ST_STREAM_SOUND);
    game->am->StartAudio("audio/Airport Lounge.mp3");
}
void LeaveHazHouse(TextAdventureGame *game)
{
    game->am->StopAudio("audio/Airport Lounge.mp3");
}

void Create_DitaBa(TextAdventureGame *game, Level *l)
{
    // setup codes
    deConCode = game->textbuffer->Random(12);
    storageCombo = game->textbuffer->Random(5);

    // add to Ke'Vr's world list
    World w;
    w.name = "Dita Ba";
    w.desc = "  Dita Ba was once a thriveing city, but has since\n"
	     "  lost it's glory due to the nuclear waste that currently\n"
	     "  decays its old streets.\n\n"
	     "  <5C>WARNIGN: NUCLEAR RADIATION STATUS: 8/10\n"
	     "  **DUE FOR CLOSURE SOON** TAKE CAUTION";
    w.dComPwd = deConCode;
    W.push_back(w);


    // build the level
    Room  *r;
    Object *o;
    BookObject *bo;
    Page *pg;
    CharacterObject *co;
    Drawer d;
    Layer y;

    r = l->AddRoom(0,0, "Dita Ba Antechamber");
    r->sDescription = "You are in Dita Ba's antechamber. It is a small sealed room with three airtight"
		      " doors and a teleportation terminal back to Ke'Vr. To the south is a door with"
		      " yellow radiation symbol printed on it, and a small window where you can see"
		      " another door just beyond it. To the east the door says Millstone Drive and"
		      " Main Street is to the west.";
    o = r->NewObject("Terminal:computer:teleporter");
    o->sLookDescription = "The rusty machine supposidly takes you back to Ke'Vr. You're not too sure.";
    o->sUseText = "";
    o->OnUse = &ToKeVrTerminal;

    r = l->AddRoom(-1, 0, "Main Street");
    r->sDescription = "Buildings line the north and south ends of Main Street. Westbound, there is"
		      " the town hall, and eastbound, the street ends leading back to the city's"
		      " antechamber. Sirens ring every couple minutes and dilapidated billboards"
		      " line the deserted street.";
    r->AddAmbientMusic("audio/test.mp3");
    o = r->NewObject("Billboard:sign");
    o->sLookDescription = "The billboard reads: "+
			  game->textbuffer->Center("**LEAVE WHILE YOU CAN**", 30)+"\n"+
			  game->textbuffer->Times(" ",21)+game->textbuffer->Center("*LEVREE OCTU JOT AWER HI*", 30)+"\n\n"+
			  game->textbuffer->Times(" ",21)+game->textbuffer->Center("Radiation is 7/10.",30)+"\n"+
			  game->textbuffer->Times(" ",21)+game->textbuffer->Center("Decay is inevitable.",30);
    r = l->AddRoom(-2,0, "Main Street");
    r->sDescription = "Although Mainstreet continues far west, cones block you from continuing. The"
		      " town hall is to the north. Sirens continue to sound.";
    r = l->AddRoom(-2, -1, "Town Hall");
    r->sDescription = "The town hall has a front desk, with many papers containing information"
		      " on the state of Dita Ba. To the west is a door that reads \"KWA Personal Only,\""
		      " although it isn't locked.";
    bo = r->NewBookObject("Report:book", OS_GLOBAL);
    bo->sLookDescription = "It's a book by Jon Turkis describing Dita Ba.";
    bo->weight = 1;
    bo->sTakeText = "You take the book.";
    pg = bo->AddPage();
    pg->AddParagraph("\n\n\n" + game->textbuffer->Center("[Dita Ba Report]"));
    pg->AddParagraph(game->textbuffer->Center("[6945]")+"\n");
    pg->AddParagraph(game->textbuffer->Center("By: Jon Turkis, KWA"));
    pg = bo->AddPage();
    pg->AddParagraph(game->textbuffer->Center("Forward")+"\n");
    pg->AddParagraph("\tDita Ba was once a prosperous city with its majour industry being the generation"
		     " of electricity, and smaller industries such as manufactureing and medicine."
		     " It featured many small businesses and had some of the happiest residents"
		     " in all of Ke'Vr. That was three thousand years ago.");
    pg->AddParagraph("\tThree thousand years ago, Dita Ba's major power company, ElCon switched from generating"
		     " electricty from biological fuel to a cheaper substance, uranium. They built new"
		     " power plants to make nuclear energy. This was fine until 3996.");
    pg = bo->AddPage();
    pg->AddParagraph(game->textbuffer->Center("Incident of 3996")+"\n");
    pg->AddParagraph("\tOn the morning of August 19, 3996, the first nuclear reactor, had a breach"
		     " in its lead containment unit. This caused radioactive particles to leak into"
		     " Dita Ba's atmosphere.");
    pg->AddParagraph("\tWhen August 20th came, there was an explosion in reactor 1, caused by the build"
		     " up of oxygen inside the reactor, which would normally be prevented by the"
		     " containment unit. Although, minor this explosion, discharged large amounts of"
		     " both unused uranium, as well as the previously burried nuclear waste that built"
		     " up for the past fifty years. It also, caused a chain reaction, causing the rest"
		     " of the reactors (2-8) to explode.");
    pg = bo->AddPage();
    pg->AddParagraph(game->textbuffer->Center("Incident of 3996 (Cont.)")+"\n");
    pg->AddParagraph("\tThe results of this were devestating. Of the city's 250,000 people, three hundred"
		     " within one mile of the plant perished in the explosions. During the next several"
		     " thousand years, the radiation took the lives of some tens of thousands of"
		     " people, including many heros, involved in the investigation and rescue"
		     " operations.");
    pg = bo->AddPage();
    pg->AddParagraph(game->textbuffer->Center("Legal Issues")+"\n");
    pg->AddParagraph("\tThe day of the incedent, KWA detective Richard Irvine attemeted to contact"
		     " Phillip Dynoid CEO ofElCon Inc. on Zetna, only to get no responce. In the"
		     " mean time, investigation of the plant, discovered ElCon's safety inspections"
		     " were long overdue. In fact they were never done at the new nuclear plant."
		     " Much of the information was provied to us in a letter from a plant employee"
		     " who sent a letter of concern to the mayor. It was sent to KWA two days before"
		     " the incedent, but did not arrive until a week after, due to heavy mail traffic."
		     " It was also found that the plant did not have the KWA regulation #2453.3b"
		     " required outter wall, to enclose nuclear waste from the outside enviroment."
		     " This meant, nuclear waste had been leaking from the site during the fifty"
		     " years of what appeared to be normal operation.");
    pg = bo->AddPage();
    pg->AddParagraph(game->textbuffer->Center("Legal Issues (Cont.)")+"\n");
    pg->AddParagraph("\tPhillip Dynoid was finally found in Klondon, Kengland on September 15th by"
		     " KWA engineers doing an inspection on its newly constructed Klondon Ear."
		     " Once spotted, Klondon't royal police caught Dynoid and KWA police had him"
		     " in custody.");
    pg->AddParagraph("\tPhillip Dynoid was convicted with disregarding KWA regulations, and the"
		     " manslaughter of all victims of the ElCon Plant Explosion. He was found guilty"
		     " and served life in KWA prison.");
    pg = bo->AddPage();
    pg->AddParagraph(game->textbuffer->Center("ElCon")+"\n");
    pg->AddParagraph("\tSince the arrest of ElCon's CEO, KWA gave the ElCom board members a chance to"
		     " avoid arrest, under the condition they helped with the cleanup of the situation."
		     " The board agreed with officials, and appointed James Berkly as the new CEO"
		     " of ElCon to lead them. ElCon, helped the KWA cleanup Dita Ba, to the best"
		     " of their ablity for the next two hundred years, before closing their last plant"
		     " on Zenon in 4211.");
    pg = bo->AddPage();
    pg->AddParagraph(game->textbuffer->Center("Current State")+"\n");
    pg->AddParagraph("\tCurrently Dita Ba's population is 0, and is deamed to be NOT SAFE to live on"
		     " by the KWA. It's radiation level is currently 8/10, where a warning is given"
		     " at 3/10. This level is extremely dangerous, and can cause DNA mutautions in"
		     " very short exposures leading to cancer. A warning has been added to Ke'Vr's"
		     " terminals, stating the condition and that it is expected to be destroyed soon."
		     " KWA is in the process of prepareing for the complete destruction of Dita Ba"
		     " and is expected to do so, in a matter of months.");
    pg->AddParagraph("\tOnce collapsed, the canister is expected to be stored in a 3x3 foot, solid"
		     " block of lead for the next million years before it is safe to dispose of.");
    pg = bo->AddPage();
    pg->AddParagraph(game->textbuffer->Center("Conclusion")+"\n");
    pg->AddParagraph("\tIf you are reading this, please leave. It is not safe for anyone. Thanks,\n");
    pg->AddParagraph("Jon Turkis, President of KWA Department of World Safety");

    r = l->AddRoom(-3, -1, "Corridor");
    r->sDescription = "You're in a tight low-lit corridore with a spoke symbol painted onto it. The"
		      " only sound is your own footsteps and an echo from your breathing.";
    o = r->NewObject("Symbol:picture:spoke");
    o->sLookDescription = "\n"
			  "   \\|/\n"
			  "  =( )=\n"
			  "   /|\\n\n";
    r = l->AddRoom(-4, -1, "Stair");
    r->sDescription = "Cold and damp concrete stairs take you down many feet below the once great"
		      " city. Cobwebs cover the railing, and your footsteps start to get louder.";
    r = l->AddRoom(-5, -1, "DeCom Room");
    r->sDescription = "You realize you're in Dita Ba's decompression room. In the center of the room"
		      " there is a large cylinder object with a giant needle, held by a pneumatic"
		      " motor. There is a display on the left.";
    o = r->NewObject("Display:computer:monitor");
    o->sLookDescription = "It's the DeCom monitor, to decompress the canister.";
    o->sUseText = "";
    o->OnUse = &DeComTerminal;

    r = l->AddRoom(1, 0, "Millstone Drive");
    r->sDescription = "You recongize the names of some of your favoirte Ke'Vr frachises such as"
		      " French Fry Prince, Subs R Us, Burger Barn, and Pizza Shack, although their"
		      " logos aren't the right color because of the decay.";

    r = l->AddRoom(2, 0, "Millstone Drive");
    r->sDescription = "The hospital is to the north. You wonder if people go there now for less money,"
		      " of course radiation poisoning is included for free.";
    r = l->AddRoom(2,-1, "Hospital");
    r->sDescription = "This is the lobby of Dita Ba Cancer Hospital. You wonder why they would"
		      " build a cancer center right next to a nuclear powerplant. At least they should"
		      " have a good stock of anti-radiation drugs. On a second look the large shelf"
		      " that normally contains the pills is empty.";
    o = r->NewObject("Shelf");
    o->sLookDescription = "From a distance the shelf is an ordianry metal shelf with empty stacks of"
			  " BeanoRad anti-radiation drugs. After stepping closer you see printed on"
			  " the boxes:\n\n"
			  "HazHouse Emergency Supply Store\n"
			  "1485 Richard Sreet\n"
			  "Dita Ba, Dita Ba, Ke'Vr\n"
			  "{Storage: "+storageCombo+"}";
    r = l->AddRoom(3, 0, "Millstone Drive");
    r->sDescription = "A billboard stands above the local shops that make up Millstone Drive."
		      " The local hospital is to the west.";
    o = r->NewObject("Billboard:sign");
    o->sLookDescription = "The billboard reads: "+
			  game->textbuffer->Center("HazHouse Emergency Store", 30)+"\n"+
			  game->textbuffer->Times(" ",21)+game->textbuffer->Center("Come buy our safety gear.", 30)+"\n\n"+
			  game->textbuffer->Times(" ",21)+game->textbuffer->Center("Don't Die.",30)+"\n"+
			  game->textbuffer->Times(" ",21)+game->textbuffer->Center("?Are You Safe?",30)+"\n\n"+
			  game->textbuffer->Times(" ",21)+game->textbuffer->Center("1485 Richard Street",30);
    r = l->AddRoom(4, 0, "Millstone Drive And Richard Street Intersection");
    r->sDescription = "To the east is the city dump, now filled with mostly processed uranium. To the"
		      " south is Richard Street. A long letter is on the ground.";
    bo = r->NewBookObject("Letter:paper", OS_LOCAL);
    bo->sLookDescription = "It's a letter to the mayor.";
    bo->weight = 0;
    bo->sTakeText = "You take the letter.";
    pg = bo->AddPage();
    pg->AddParagraph("\n\n"+game->textbuffer->Center("Mayor Robertson"));
    pg = bo->AddPage();
    pg->AddParagraph("\tGood day, Sir. I'm Jack Floss, an employee of ElCon, and I would like"
		     " to share my concerns about Dita Ba's nuclear power plant.");
    pg->AddParagraph("\tI'm not sure who this should go to, but I can say that it is very urgent.");
    pg = bo->AddPage();
    pg->AddParagraph("\tThe power plant is not in good condition, and lacks certain safety features"
		     " such as an outter wall. Also, It was built fast, and with cheap material."
		     " I worry it might break soon. Before it was built, we had inspections on"
		     " a bi-monthly basis. I don't belive a single inspection has been done. I"
		     " presume people are already aware of this, but nothing has been done so"
		     " far to resolve it.");
    pg->AddParagraph("\tThe other day, smoke was leaking out of reactor 1, and we called the CEO to"
		     " check on the plant. He said it was fine, and to shut up about it. I worry"
		     " that it was not fine, and a disater is about to strike.");
    pg = bo->AddPage();
    pg->AddParagraph("\tPlease keep my name anonymous, and understand I am only writing this"
		     " to ensure the town's safety. Nothing else is more important. Please check"
		     " it out.\n\n\n");
    pg->AddParagraph("Sincerly,");
    pg->AddParagraph("Jack Floss");


    r = l->AddRoom(5, 0, "Dump");
    r->sDescription = "You no longer belive that this was once a thriving city after seeing the garbage."
		      " Hundreds of thousands of pill bottles, form a thick layer of plastic which"
		      " will probably take a million years to decompose. It reminds you of Earth."
		      " Under some shallow sections you can see dull metallic rocks, that appear to"
		      " be uranium. You can almost smell the radon gas emiting from its decay. All your"
		      " scientific background tells you radon was odorless.";
    o = r->NewObject("Uranium:rock", OS_LOCAL);
    o->sLookDescription = "The uranium is a dull silver radioactive rock. It happens to be Uranium-235"
			  " with a half life of seven hundred million years. As it slowly decays, radon"
			  " gas is created, which is highly radioactive itself.";
    o->sTakeText = o->sUseText = "";
    o->weight = 0;
    o->OnUse = o->OnTake = &OnTouchUranium;

    r = l->AddRoom(4, 1, "Richard Street");
    r->sDescription = "Richard Street is just as desolate as all the rest. The smog, makes the"
		      " building lights glare.";

    r = l->AddRoom(4, 2, "Richard Street");
    r->sDescription = "There is a man leaning up against Subs R Us. He appears to be alive, yet very"
		      " tired.";
    co = r->NewCharacterObject("Man:person", OS_GLOBAL);
    co->sLookDescription = "He has a black hat, and a brown suit.";
    co->OnTalk = &OnTalkToMan;
    co->sTakeText = "You put the man on your sholders and carry him.";
    co->weight = 5;

    r = l->AddRoom(4,3, "Richard Street");
    r->sDescription = "To the east is the much discussed HazHouse shop.";

    r = l->AddRoom(5, 3, "HazHouse");
    r->sDescription = "The many shelves are empty, and the signs are taken down. Adhesive is still"
		      " stuck to some of the metal racks reveiling informative product names such as"
		      " 'ar' and 'v' and 'dyn.' There is a door with an alphanumeric keypad lock in "
		      " the southern side of the room.";
    o = r->NewObject("Keypad:lock:keyboard:code");
    o->sLookDescription = "It is a full sized keypad, with all letters and numbers.";
    o->sUseText = "";
    o->OnUse = &OnUseStorageKeyPad;

    r = l->AddRoom(5, 4, "HazHouse Storage");
    r->sDescription = "The storage room has many boxes of extra emergency preperation"
		      " gear that was not placed on shelves. You see a note on the ground.";
    r->OnEnterRoom = &EnterHazHouse;
    r->OnExitRoom  = &LeaveHazHouse;
    o = r->NewObject("Note:notice:memo", OS_LOCAL);
    o->sLookDescription = "The note reads:\n\n"
			  "Dear Reader of This Note,\n\n"
			  "   If you have obtained this note, most likely Dita Ba is in major trouble"
			  " and is on its way to collapse. Once everyone is out of Dita Ba, please"
			  " go to Dita Ba's DeCom center and enter the code: \n" + deConCode;
    o->sTakeText = "You take the note";
    o->weight = 0;

    r = l->AddRoom(4, 4, "Richard Street");
    r->sDescription = "Cones block the rest of the street. You can see a flood of Plutonium a couple"
		      " hundred feet past the cones.";
    l->OpenAllDoors();
    l->CloseDoors(5,4, NORTH | WEST);
    l->sLevelIntro = "You fall in the sealed antechamber of Dita Ba.";
    l->startX = 0;
    l->startY = 0;
    l->OnLoad = &Load_DitaBa;
    l->OnSave = &Save_DitaBa;

    l->AddAmbientMusic("audio/OverCoat__Memories_EP__1__Reflections_64kb.mp3");
    l->AddAmbientMusic("audio/ercaMusSeg02-1.ogg");
}



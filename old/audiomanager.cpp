#include "audiomanager.h"
#include "mainwindow.h"
#include <QDebug>

AudioManager::AudioManager(TextAdventureGame *g)
{
    game = g;
    for(int i=0; i<MAX_AUDIO_CHANNELS; i++)
    {
	C[i] = new AudioChannel;
	C[i]->AFid = -1;
	C[i]->active = false;
	C[i]->c = NULL;
    }

    FMOD_RESULT       result;
    unsigned int      version;

    /*
	Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    ERRCHECK(result, 1);
    result = FMOD_System_GetVersion(system, &version);
    ERRCHECK(result, 2);

    if (version < FMOD_VERSION)
    {
	QMessageBox::critical(NULL, "FMOD ERROR", "You are using an old version "
			      "of FMOD "+QString::number(version)+". This program "
			      "requires "+QString::number(FMOD_VERSION)+"!");
	return;
    }

    result = FMOD_System_Init(system, MAX_AUDIO_CHANNELS, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result, 3);

    fMaster = 1;
    fAmbient = 0.5;
    fSound = 1;
}

AudioManager::~AudioManager()
{
    FMOD_RESULT       result;
    for(int i=0; i<S.size(); i++)
    {
	result = FMOD_Sound_Release(S[i]->s);
	(result);
	delete S[i];
    }
    S.clear();

    for(int i=0; i<P.size(); i++)
    {
	delete P[i];
    }
    P.clear();

    for(int i=0; i<MAX_AUDIO_CHANNELS; i++)
    {
	delete C[i];
    }
    result = FMOD_System_Close(system);
    ERRCHECK(result, 4);
    result = FMOD_System_Release(system);
    ERRCHECK(result, 5);
}

AudioFile *AudioManager::LoadAudio(QString fl, SoundType st, int volume)
{
    FMOD_SOUND *s;
    FMOD_RESULT result;

    AudioFile *tmpaf = GetAudioFile(fl);
    if(tmpaf != NULL)
	return tmpaf;

    if(st == ST_AMBIENT || st == ST_STREAM_SOUND)
	result = FMOD_System_CreateStream(system, fl.toStdString().c_str(),
				FMOD_DEFAULT, 0, &s);
    else
	result = FMOD_System_CreateSound(system, fl.toStdString().c_str(),
				FMOD_DEFAULT, 0, &s);

    ERRCHECK(result, fl, 6);
    AudioFile *af = new AudioFile;
    af->s = s;
    af->flName = fl;
    af->level = (float)volume / 100;
    af->type = st;
    af->CHid = -1;
    af->paused = true;
    af->loop = false;
    af->pid = -1;
    S.push_back(af);
    return af;
}

void AudioManager::StartAudio(QString fl, int c)
{
    FMOD_RESULT result;
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
    {
	af = LoadAudio(fl, ST_SOUND, 100);
    }
    // find free channel
    int cid = -1;
    if(c > -1)
    {
	cid = c;
    }
    else
    {
	for(int i=0; i<MAX_AUDIO_CHANNELS; i++)
	{
	    if(!C[i]->active)
	    {
		cid = i;
		break;
	    }
	}
	if(cid == -1)
	{
	    // all channels taken up.
	    return;
	}
    }
    C[cid]->active = true;
    C[cid]->AFid = S.indexOf(af);
    af->CHid = cid;
    result = FMOD_System_PlaySound(system, (FMOD_CHANNELINDEX)cid, af->s, false,
				   &C[cid]->c);

    ERRCHECK(result, 7);
    af->paused = false;
    AutoConfigSound(af);
}

void AudioManager::StopAudio(QString fl)
{
    FMOD_RESULT result;
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
	return;
    if(af->CHid < 0) // sound not engaged
	return;
    int cid = af->CHid;
    result = FMOD_Channel_Stop(C[cid]->c);
    ERRCHECK(result, 8);
    C[cid]->AFid = -1;
    C[cid]->active = false;
    C[cid]->c = NULL;
    af->CHid = -1;
    af->paused = true;
}

void AudioManager::SetVolume(QString fl, int volume)
{
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
	return;
    af->level = (float)volume / 100;
    if(af->CHid > -1)
	AutoConfigSound(af);
}

void AudioManager::SetPause(QString fl, bool pause)
{
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
	return;
    if(af->CHid > -1)
    {
	af->paused = pause;
	AutoConfigSound(af);
    }
}

void AudioManager::SetLoop(QString fl, bool loop)
{
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
	return;
    af->loop = loop;
    if(af->CHid > -1)
    {
	AutoConfigSound(af);
    }
}

void AudioManager::AutoConfigSound(AudioFile *f)
{
    FMOD_RESULT result;
    int cid = f->CHid;

    // VOLUME
    float vol = fMaster * f->level;
    if(f->type == ST_AMBIENT)
	vol = vol * fAmbient;
    else
	vol = vol * fSound;
    if(vol > 1)
	vol = 1;
    if(vol < 0)
	vol = 0;
    result = FMOD_Channel_SetVolume(C[cid]->c, vol);
    ERRCHECK(result, 9);

    // PAUSE
    result = FMOD_Channel_SetPaused(C[cid]->c, f->paused);
    ERRCHECK(result, 10);

    // LOOP
    if(f->loop)
	result = FMOD_Channel_SetMode(C[cid]->c, FMOD_LOOP_NORMAL);
    else
	result = FMOD_Channel_SetMode(C[cid]->c, FMOD_LOOP_OFF);
    ERRCHECK(result, 11);
}

AudioFile *AudioManager::GetAudioFile(QString fl)
{
    fl = fl.toLower();
    for(int i=0; i<S.size(); i++)
    {
	if(S[i]->flName == fl)
	{
	    return S[i];
	}
    }
    return NULL;
}

Playlist *AudioManager::GetPlaylist(QString pname)
{
    pname = pname.toLower();
    for(int i=0; i<P.size(); i++)
    {
	if(P[i]->name == pname)
	{
	    return P[i];
	}
    }
    return NULL;
}

bool AudioManager::IsEngaged(QString fl)
{
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
	return false;
    if(af->CHid > -1)
	return true;
    return false;
}

bool AudioManager::IsPlaying(QString fl)
{
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
	return false;
    if(IsEngaged(fl))
    {
	if(!af->paused)
	{
	    return true;
	}
    }
    return false;
}

void AudioManager::CreatePlaylist(QString pname)
{
    if(GetPlaylist(pname) != NULL)
	return;
    Playlist *p = new Playlist;
    p->name = pname.toLower();
    p->cid = -1;
    p->curS = -1;

    P.push_back(p);
}

void AudioManager::AddToPlaylist(QString pname, QString fl)
{
    Playlist *p = GetPlaylist(pname);
    if(p == NULL)
	return;
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
	af = LoadAudio(fl, ST_SOUND, 100);
    p->S.push_back(af);
    af->pid = P.indexOf(p);
}

void AudioManager::RemoveFromPlaylist(QString pname, QString fl)
{
    Playlist *p = GetPlaylist(pname);
    if(p == NULL)
	return;
    AudioFile *af = GetAudioFile(fl);
    if(af == NULL)
	return;
    af->pid = -1;
    int i = p->S.indexOf(af);
    if(i > -1)
	p->S.removeAt(i);
}

void AudioManager::StartPlaylist(QString pname)
{
    Playlist *p = GetPlaylist(pname);
    if(p == NULL)
	return;

    if(p->cid < 0)
    {
	for(int i=0; i<MAX_AUDIO_CHANNELS; i++)
	{
	    if(!C[i]->active)
	    {
		p->cid = i;
		break;
	    }
	}
	if(p->cid == -1)
	{
	    // all channels taken up.
	    return;
	}
    }
    if(p->S.size() < 1)
	return;
    StartAudio(p->S[0]->flName, p->cid);
    p->curS = 0;
}

void AudioManager::StopPlaylist(QString pname)
{
    Playlist *p = GetPlaylist(pname);
    if(p == NULL)
	return;

    if(p->curS < 0)
	return;
    StopAudio(p->S[p->curS]->flName);
    p->curS = -1;
}

void AudioManager::SetPlaylistPause(QString pname, bool pause)
{
    Playlist *p = GetPlaylist(pname);
    if(p == NULL)
	return;

    if(p->curS < 0)
	return;
    SetPause(p->S[p->curS]->flName, pause);
}

bool AudioManager::IsPlaylistEngaged(QString pname)
{
    Playlist *p = GetPlaylist(pname);
    if(p == NULL)
	return false;

    if(p->cid > -1)
	return true;

    return false;
}

bool AudioManager::IsPlaylistPlaying(QString pname)
{
    Playlist *p = GetPlaylist(pname);
    if(p == NULL)
	return false;

    if(IsPlaylistEngaged(pname) && p->curS > -1)
    {
	if(!p->S[p->curS]->paused)
	{
	    return true;
	}
    }
    return false;
}

void AudioManager::PlaylistNextSong(int pid)
{
    Playlist *p = P[pid];
    if(p == NULL)
	return;

    if(p->curS < 0)
	return;
    p->curS ++;
    if(p->curS >= p->S.size())
	p->curS = 0;
    StartAudio(p->S[p->curS]->flName, p->cid);
}

void AudioManager::Update()
{
    // find out what is playing & what stopped
    FMOD_RESULT result;
    for(int i=0; i<MAX_AUDIO_CHANNELS; i++)
    {
	if(C[i]->c != NULL)
	{
	    FMOD_BOOL playing, paused;
	    result = FMOD_Channel_IsPlaying(C[i]->c, &playing);
	    ERRCHECK(result, 12);
	    result = FMOD_Channel_GetPaused(C[i]->c, &paused);
	    ERRCHECK(result, 13);
	    if(!playing || paused)
	    {
		if(paused)
		{
		    if(C[i]->AFid > -1 && C[i]->AFid < S.size())
		    {
			S[C[i]->AFid]->CHid = i;
			S[C[i]->AFid]->paused = true;
		    }
		}
		else // stopped
		{
		    if(C[i]->AFid > -1 && C[i]->AFid < S.size())
		    {
			if(S[C[i]->AFid]->loop)
			{
			    result = FMOD_Channel_SetPosition(C[i]->c, 0, FMOD_TIMEUNIT_MS);
			    ERRCHECK(result, 14);
			    continue; // it temperarly stopped
			}
			if(S[C[i]->AFid]->pid > -1)
			{
			    PlaylistNextSong(S[C[i]->AFid]->pid);
			    continue; // It's a playlist, so we continue to the next channel
			}
			S[C[i]->AFid]->CHid = -1;
			S[C[i]->AFid]->paused = true;
		    }
		    C[i]->AFid = -1;
		    C[i]->active = false;
		    C[i]->c = NULL;
		}
	    }
	    else
	    {
		if(C[i]->AFid > -1 && C[i]->AFid < S.size())
		{
		    S[C[i]->AFid]->CHid = i;
		    S[C[i]->AFid]->paused = false;
		}
		C[i]->active = true;
	    }
	}
	else
	{
	    if(C[i]->AFid > -1 && C[i]->AFid < S.size())
	    {
		S[C[i]->AFid]->CHid = -1;
		S[C[i]->AFid]->paused = true;
	    }
	    C[i]->AFid = -1;
	    C[i]->active = false;
	    C[i]->c = NULL;
	}
    }

    /*qDebug("State: %d", (int)o->state());
    qDebug(o->errorString().toStdString().c_str());*/
}

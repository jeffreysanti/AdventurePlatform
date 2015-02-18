#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "stdafx.h"
#include "textbuffer.h"

#define MAX_AUDIO_CHANNELS 16

class TextAdventureGame;

enum SoundType{
    ST_AMBIENT,
    ST_SOUND,
    ST_STREAM_SOUND
};

struct AudioChannel
{
    int AFid;
    bool active;
    FMOD_CHANNEL *c;
};

struct AudioFile
{
    QString flName;
    FMOD_SOUND *s;
    SoundType type;
    float level;
    int CHid;
    bool paused; // internal use (for setting state)
    bool loop;
    int pid;
};

struct Playlist
{
    QString name;
    QList<AudioFile*>S;
    int cid;
    int curS;
};

class AudioManager
{
public:
    AudioManager(TextAdventureGame *g);
    ~AudioManager();

    void Update();

    AudioFile *LoadAudio(QString fl, SoundType s, int volume = 100);
    void StartAudio(QString fl, int c=-1);
    void StopAudio(QString fl);
    void SetVolume(QString fl, int volume=100);
    void SetPause(QString fl, bool pause);
    void SetLoop(QString fl, bool loop);

    void CreatePlaylist(QString pname);
    void AddToPlaylist(QString pname, QString fl);
    void RemoveFromPlaylist(QString pname, QString fl);
    void StartPlaylist(QString pname);
    void StopPlaylist(QString pname);
    void SetPlaylistPause(QString pname, bool pause);
    bool IsPlaylistEngaged(QString pname);
    bool IsPlaylistPlaying(QString pname);

    bool IsEngaged(QString fl);
    bool IsPlaying(QString fl);


protected:

    FMOD_SYSTEM      *system;

    QList<AudioFile*> S;
    AudioChannel *C[MAX_AUDIO_CHANNELS];
    QList<Playlist*> P;

    float fMaster;
    float fAmbient;
    float fSound;

    AudioFile *GetAudioFile(QString fl);
    Playlist *GetPlaylist(QString pname);

    void PlaylistNextSong(int pid);

    TextAdventureGame *game;

    void AutoConfigSound(AudioFile *f);
};

inline void ERRCHECK(FMOD_RESULT result, int num=0)
{
    if (result != FMOD_OK)
    {
	QMessageBox::critical(NULL, "FMOD ERROR", QString::number(result)+"\n"+
			      QString(FMOD_ErrorString(result)) + "\n" + QString::number(num));
	return;
    }
}

inline void ERRCHECK(FMOD_RESULT result, QString extra, int num=0)
{
    if (result != FMOD_OK)
    {
    QMessageBox::critical(NULL, "FMOD ERROR", QString::number(result)+"\n"+ extra + "\n" +
                  QString(FMOD_ErrorString(result)) + "\n" + QString::number(num));
    return;
    }
}

#endif // AUDIOMANAGER_H

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_MUSIC 25
#define MAX_FX 100


class ModuleAudio :public Module 
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Music* const LoadMusic(const char* path);
	Mix_Chunk* const LoadEffect(const char* path);

	void PlayMusic(Mix_Music* mus_to_play, int reps = -1);
	void PlaySoundEffects(Mix_Chunk* fx_to_play);
	void UnloadMusic(Mix_Music* mus);
	void UnloadFx(Mix_Chunk* fx);

public:
	
	uint last_song = 0;
	uint last_fx = 0;


	Mix_Music* mus[MAX_MUSIC];

	Mix_Chunk* sound_fx[MAX_FX];

};

#endif

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_MUSIC 25
#define MAX_FX 25


class ModuleAudio :public Module 
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Music* const LoadMusic(const char* path);
	Mix_Chunk* const LoadChunk(const char* path);
	bool UnloadMusic(Mix_Music* music_audio);
	bool UnloadChunk(Mix_Chunk* chunk);

public:
	Mix_Music* music[MAX_MUSIC] = {nullptr};
	Mix_Chunk* fx[MAX_FX] = {nullptr};
};

#endif

#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module() {

}

ModuleAudio::~ModuleAudio() {

}

bool ModuleAudio::Init() {
	LOG("Init Mixer library");
	bool ret = true;

	// load support for the AUDIO format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);
	Mix_OpenAudio(22050, AUDIO_S8, 2, 4096);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. MIX_Init: %s", Mix_GetError());
		ret = false;
	}

	for (int i = 0; i < MAX_MUSIC; ++i) {
		if (music[i] != nullptr) {
			Mix_PlayMusic(music[0], 1);
		}
		if (fx[i] != nullptr) {
			Mix_PlayChannel(-1, fx[0], 0);
		}
	}

	return ret;
}

bool ModuleAudio::CleanUp() {
	LOG("Freeing audios and Mixer library");

	for (uint i = 0; i < MAX_MUSIC; ++i) {
		if (music[i] != nullptr) {
			Mix_FreeMusic(music[i]);
		}
	}

	for (uint i = 0; i < MAX_FX; ++i) {
		if (fx[i] != nullptr) {
			Mix_FreeChunk(fx[i]);
		}
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

Mix_Music* const ModuleAudio::LoadMusic(const char* path) {
	int num = 0;

	Mix_Music* mus = nullptr;

	mus = Mix_LoadMUS(path);
	if(!mus){
		LOG("Mix Error:", Mix_GetError());
		return nullptr;
	}

	for (int i = 0; i < MAX_MUSIC; ++i) {
		if (music[i] == nullptr) {
			num = i;
			i = MAX_MUSIC;
		}
	}

	music[num] = mus;

	return music[num];
}

Mix_Chunk* const ModuleAudio::LoadChunk(const char* path) {
	int num = 0;

	Mix_Chunk* effect = nullptr;

	effect = Mix_LoadWAV(path);
	if (!effect) {
		LOG("Mix Error:", Mix_GetError());
		return nullptr;
	}

	for (int i = 0; i < MAX_FX; ++i) {
		if (fx[i] == nullptr) {
			num = i;
			i = MAX_FX;
		}
	}

	fx[num] = effect;


	return fx[num];
}

bool ModuleAudio::UnloadMusic(Mix_Music* music_audio)
{
	bool ret = false;

	if (music_audio != nullptr)
	{
		for (int i = 0; i < MAX_MUSIC; ++i)
		{
			if (music[i] == music_audio)
			{
				music[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FreeMusic(music_audio);
	}

	return ret;
}

bool ModuleAudio::UnloadChunk(Mix_Chunk* chunk)
{
	bool ret = false;

	if (chunk != nullptr)
	{
		for (int i = 0; i < MAX_MUSIC; ++i)
		{
			if (fx[i] == chunk)
			{
				fx[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FreeChunk(chunk);
	}

	return ret;
}

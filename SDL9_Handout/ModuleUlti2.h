#ifndef __MODULEULTI2_H__
#define __MODULEULTI2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleUlti2 : public Module
{
public:
	ModuleUlti2();
	~ModuleUlti2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Particle sword, sword_idle;
	SDL_Texture* graphics = nullptr;
	Mix_Chunk* ulti_fx = nullptr;
	int posy = 20;
	
	bool timer = false;
	int current_time = 0;
	int time_on_entry = 0;

	bool timer_1 = false;
	int current_time_1 = 0;
	int time_on_entry_1 = 0;

	bool interval = false;
	int current_interval = 0;
	int interval_on_entry = 0;

	int random = 0;
	int aux = 0;

	SDL_Rect ulti_collider;
	Collider* coll = nullptr;
};

#endif // __MODULEULTI2_H__
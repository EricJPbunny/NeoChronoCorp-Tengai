#ifndef __MODULEULTI3_H__
#define __MODULEULTI3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleUlti3 : public Module
{
public:
	ModuleUlti3();
	~ModuleUlti3();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Particle sword, sword_idle;
	SDL_Texture* graphics = nullptr;
	int posy = 20;
	
	bool timer = false;
	int current_time = 0;
	int time_on_entry = 0;
};

#endif // __MODULEULTI3_H__
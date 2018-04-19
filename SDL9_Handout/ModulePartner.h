#ifndef __MODULE_PARTNER__H
#define __MODULE_PARTNER__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModulePlayer.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

enum partner_state {
	NOT_EXISTING,
	LEVEL_ONE,
	LEVEL_TWO,
	LEVEL_ONE_CHARGE,
	LEVEL_TWO_CHARGE
};

class ModulePartner : public Module 
{
public:
		ModulePartner();
		~ModulePartner();

		bool Start();
		update_status Update();
		bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation spawn;
	Animation iddle;
	Animation charging;
	Animation spawn2;
	Animation iddle2;
	Animation charging2;
	fPoint position;
	partner_state state = NOT_EXISTING;
	
};

#endif

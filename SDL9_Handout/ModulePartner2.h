#ifndef __MODULE_PARTNER2__H
#define __MODULE_PARTNER2__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModulePlayer.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

enum partner_state_2 {
	NOT_EXISTING_2,
	SPAWN,
	LEVEL_ONE_2,
	LEVEL_ONE_CHARGE_2,
	SHOT,
};

class ModulePartner2 : public Module 
{
public:
		ModulePartner2();
		~ModulePartner2();

		bool Start();
		update_status Update();
		bool CleanUp();
private:
	void CheckState();
	void PerformActions();

public:
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation* current_animation_2 = nullptr;
	Animation spawn, spawn2;
	Animation spawn_reverse, spawn_reverse2;
	Animation iddle, iddle2;
	Animation charging, charging2;
	fPoint position;
	partner_state_2 state = NOT_EXISTING_2, state_2 = NOT_EXISTING_2;
	bool exist = false, exist_2 = false, movement = true;
	
};

#endif

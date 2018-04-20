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
	LEVEL_ONE_2,
	LEVEL_TWO_2,
	LEVEL_ONE_CHARGE_2,
	LEVEL_TWO_CHARGE_2,
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
	Animation spawn;
	Animation iddle;
	Animation charging;
	Animation spawn2;
	Animation iddle2;
	Animation charging2;
	fPoint position;
	partner_state_2 state = NOT_EXISTING_2;
	bool exist = false;
	
};

#endif

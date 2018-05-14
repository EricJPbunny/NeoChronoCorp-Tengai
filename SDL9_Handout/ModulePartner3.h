#ifndef __MODULE_PARTNER3__H
#define __MODULE_PARTNER3__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
//#include "ModulePlayer3.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

enum partner_state_3 {
	NOT_EXISTING,
	LEVEL_ONE,
	LEVEL_ONE_CHARGE,
	LEVEL_FOUR,
	LEVEL_FOUR_CHARGE,
	SPAWN,
	FIRE,
};

class ModulePartner3 : public Module
{
public:
	ModulePartner3();
	~ModulePartner3();

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
	Animation decharging;
	Animation charged;
	fPoint position;
	partner_state_3 state = NOT_EXISTING;
};

#endif
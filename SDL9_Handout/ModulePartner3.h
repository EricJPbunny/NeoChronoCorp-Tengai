#ifndef __MODULE_PARTNER3__H
#define __MODULE_PARTNER3__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModulePlayer3.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

enum partner_state_3 {
	NOT_EXISTING_3,
	LEVEL_ONE_3,
	LEVEL_ONE_CHARGE_3,
	LEVEL_TWO_3,
	LEVEL_TWO_CHARGE_3,
	LEVEL_THREE_3,
	LEVEL_THREE_CHARGE_3,
	LEVEL_FOUR_3,
	LEVEL_FOUR_CHARGE_3,
	SPAWN_3,
	FIRE_3,
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
	Animation spawn_reverse;
	Animation pre_shot, shot;
	fPoint position;
	partner_state_3 state = NOT_EXISTING_3;

	bool time_shoot = true, exist = false;

	bool shot_delay = true;
	int shot_current = 0;
	int shot_entry = 0;

	int time_on_entry = 0;
	int current_time = 0;
};

#endif
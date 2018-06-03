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
	SPAWN_3,
	IDLE_SOCRATES,
	CHARGING,
	FIRE_3,
	DECHARGING,
	DESPAWN_3,
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
	Animation charging, decharging;
	Animation spawn_reverse;
	Animation pre_shot, shot;
	fPoint position;
	partner_state_3 state = NOT_EXISTING_3;

	bool time_shoot = true, movement = true, time_socrates = true, exist = false;

	bool shot_delay = true;
	int shot_current = 0;
	int shot_entry = 0;

	int time_on_entry = 0;
	int current_time = 0;
	bool charged_shoot = false;

	int increaser = 0;
	bool multiple_shot = false;
	bool multiple_shot_2 = false;

	bool shot_space_3;
	bool pressed_space_3;
	bool release_space_3;
	
};

#endif
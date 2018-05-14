#ifndef __MODULE_PARTNER2__H
#define __MODULE_PARTNER2__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModulePlayer2.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

enum partner_state_2 {
	NOT_EXISTING_2,
	SPAWN_2,
	DESPAWN,
	LEVEL_ONE_2,
	LEVEL_ONE_CHARGE_2,
	SHOT_2,
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
	Animation* current_animation_3 = nullptr;
	Animation spawn, spawn2, spawn3;
	Animation spawn_reverse, spawn_reverse2, spawn_reverse3;
	Animation iddle, iddle2, iddle3;
	Animation charging, charging2, charging3;
	fPoint position;
	partner_state_2 state = NOT_EXISTING_2, state_2 = NOT_EXISTING_2, state_3 = NOT_EXISTING_2;
	bool exist = false, exist_2 = false, exist_3 = false, movement = true, time_mirror = true, time_shoot = true, time_mirror_2 = true, time_shoot_2 = true, time_mirror_3 = true, time_shoot_3 = true;
	bool charged_shoot = false;

	int time_on_entry = 0;
	int current_time = 0;
	int time_on_entry_2 = 0;
	int current_time_2 = 0;
	int time_on_entry_3 = 0;
	int current_time_3 = 0;

	bool shot_delay = true;
	int shot_current = 0;
	int shot_entry = 0;

	bool shot_delay_2 = true;
	int shot_current_2 = 0;
	int shot_entry_2 = 0;

	bool shot_delay_3 = true;
	int shot_current_3 = 0;
	int shot_entry_3 = 0;

	int num_bullet = 1;
	int num_bullet_2 = 1;
	int num_bullet_3 = 1;

};

#endif

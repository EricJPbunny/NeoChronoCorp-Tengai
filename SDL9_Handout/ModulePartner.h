#ifndef __MODULE_PARTNER__H
#define __MODULE_PARTNER__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
#include "ModulePlayer.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

enum partner_state {
	NOT_EXISTING,
	LEVEL_ONE,
	LEVEL_ONE_CHARGE,
	LEVEL_FOUR,
	LEVEL_FOUR_CHARGE,
	SPAWN,
	EGG_SHOT,
	CAT_SHOT,
};

class ModulePartner : public Module
{
public:
	ModulePartner();
	~ModulePartner();
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
	Animation egg_shot;
	fPoint position;
	partner_state state = NOT_EXISTING;
	Path shot_movement;
	int aux;
	bool time_shoot = true, exist = false, time_cat = true;

	bool shot_delay = true;
	int shot_current = 0;
	int shot_entry = 0;

	int time_on_entry = 0;
	int current_time = 0;

	bool create_bullet = true, update_bullet = false;
};

#endif
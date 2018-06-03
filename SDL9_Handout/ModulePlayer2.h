#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

enum player_state_2 {
	SPAWN_PLAYER_2,
	IDLE_2,
	BACKWARD_2,
	GO_BACKWARD_2,
	BACK_IDLE_2,
	WALK_2,
	SPIN_2,
	DEATH_2,
	POST_DEATH_2,
};

class ModulePlayerTwo : public Module
{
public:
	ModulePlayerTwo();
	~ModulePlayerTwo();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
private:
	void CheckState();
	void PerformActions();

public:

	int aux = 0, aux1 = 0;
	int alpha_player = 255;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* player_death = nullptr; 
	Collider* coll = nullptr;
	Collider* hitbox = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation intermediate;
	Animation spin;
	Animation spin_circle;
	Animation death_circle;
	Animation intermediate_return;
	SDL_Rect death;
	bool destroyed = false;
	bool check_death = false, check_spawn = true;
	player_state_2 state = IDLE_2;
	int power_up = 0;
	fPoint position;
	fPoint aux_spin;
	fPoint aux_death;

	bool time = true;
	bool blink = true;

	int time_on_entry = 0;
	int current_time = 0;

	int blink_on_entry = 0;
	int blink_time = 0;

	bool input = true;
	bool spin_pos = false;
	bool death_pos = false;
	bool explosion = false;

	bool pressed_W;
	bool pressed_A;
	bool pressed_S;
	bool pressed_D;

	bool shot_space;
	bool ulti_button;

	bool press_A;
	bool press_W;

	bool release_A;
	bool release_W;

	bool released_W;
	bool released_A;

	Uint8 key;
};


#endif

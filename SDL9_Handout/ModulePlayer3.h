#ifndef __ModulePlayer3_H__
#define __ModulePlayer3_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;
struct Collider;

enum player_state_3 {
	SPAWN_PLAYER_3,
	IDLE_3,
	BACKWARD_3,
	GO_BACKWARD_3,
	BACK_IDLE_3,
	SPIN_3,
	DEATH_3,
	POST_DEATH_3,
	ULTI_3,
};
class ModulePlayer3 : public Module
{
public:
	ModulePlayer3();
	~ModulePlayer3();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
private:
	void CheckState();
	void PerformActions();

public:

	int aux = 0;
	int aux1 = 0;
	int alpha_player = 255;
	Mix_Chunk* k_power_down = nullptr;
	Collider* coll = nullptr;
	Collider* hitbox = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* player_death = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation intermediate;
	Animation spin;
	Animation spin_circle;
	Animation death_circle;
	Animation intermediate_return;
	Animation ulti;
	SDL_Rect death;
	fPoint position;
	fPoint aux_spin;
	fPoint aux_death;
	bool destroyed = false;
	bool check_death = false, check_spawn = true;
	player_state_3 state = IDLE_3;
	int power_up = 0;

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
	
	bool pressed_up;
	bool pressed_left;
	bool pressed_down;
	bool pressed_right;

	bool press_left;
	bool press_up;

	bool release_left;
	bool release_up;

	bool released_up;
	bool released_left;

	bool shot_ctrl;
	bool ulti_button;

	bool ulti_on = false;
	
	Uint8 key;

};

#endif
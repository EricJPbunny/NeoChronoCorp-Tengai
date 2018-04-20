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
	IDLE_2,
	BACKWARD_2,
	GO_BACKWARD_2,
	BACK_IDLE_2,
	WALK_2,
	SPIN_2,
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
	SDL_Texture* graphics = nullptr;
	SDL_Texture* player_death = nullptr; 
	Collider* coll = nullptr;
	Animation* current_animation = nullptr;
	Animation walk;
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
	player_state_2 state = IDLE_2;
	int power_up = 0;
	fPoint position;

};


#endif

#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	int aux = 0;
    int aux1 = 0;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* player_death = nullptr;
	Animation* current_animation = nullptr;
	Animation walk;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation intermediate;
	Animation spin;
	Animation spin_circle;
	Animation death_circle;
	Animation intermediatereturn;
	SDL_Rect death;
	fPoint position;
	bool destroyed = false;
};

#endif
#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;
struct Collider;

enum player_state {
	SPAWN_PLAYER,
	IDLE,
	BACKWARD,
	GO_BACKWARD,
	BACK_IDLE,
	WALK,
	SPIN,
	DEATH,
	POST_DEATH,
};
class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

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
	Collider* coll = nullptr;
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
	Animation intermediate_return;
	SDL_Rect death;
	fPoint position;
	bool destroyed = false;
	bool check_death = false, check_spawn = true;
	player_state state = IDLE;

	bool time = true;
	bool blink = true;

	int time_on_entry = 0;
	int current_time = 0;

	int blink_on_entry = 0;
	int blink_time = 0;

	bool input = true;
	
};

#endif
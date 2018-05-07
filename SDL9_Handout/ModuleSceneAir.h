#ifndef __MODULESCENEFOREST_H__
#define __MODULESCENEFOREST_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
struct SDL_Texture;

class ModuleSceneAir : public Module
{
public:
	ModuleSceneAir();
	~ModuleSceneAir();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* mus = nullptr;
	Mix_Music* boss = nullptr;
	Mix_Music* level_completed = nullptr;
	Mix_Chunk* select_koyori = nullptr;
	Mix_Chunk* select_sho = nullptr;
	Collider* coll_left = nullptr;
	Collider* coll_right = nullptr;
	Collider* coll_up = nullptr;
	Collider* coll_down = nullptr;
	Collider* coll_trigger = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* laterals = nullptr;
	SDL_Texture* mid = nullptr;
	SDL_Texture* mid1 = nullptr;
	SDL_Texture* end = nullptr;
	SDL_Rect MountainBg,SkyOne,SkyTwo,SkyThree,SkyFour;
	SDL_Rect fader, fademid;
	float posx = 7000, posy = -480, grassy = 185;
	bool fade = true;
	float alpha_mid = 0, alpha_mid1 = 255, alpha_graph2 = 255, alpha_graph1 = 0, alpha_end = 0;
	float speed = 10.5;
	int aux_time = 0;

	bool god_mode = false;
};

#endif // __MODULESCENEFOREST_H__
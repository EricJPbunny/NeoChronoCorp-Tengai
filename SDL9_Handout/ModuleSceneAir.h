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
	Mix_Chunk* select_junis = nullptr;
	Collider* coll_left = nullptr;
	Collider* coll_right = nullptr;
	Collider* coll_up = nullptr;
	Collider* coll_down = nullptr;
	Collider* coll_trigger = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;
	SDL_Texture* laterals = nullptr;
	SDL_Texture* mid = nullptr;
	SDL_Texture* mid1 = nullptr;
	SDL_Texture* end = nullptr;
	SDL_Rect MountainBg, SkyOne, SkyTwo, SkyThree, SkyFour, FloorOne, FloorTwo, FloorThree, FloorFour, FloorFive, BigSky, BigSkyTwo, BigSkyThree, exterior_ship,BigSkyParalaxOne, BigSkyParalaxTwo;
	SDL_Rect destroyed_ship, inside_2, grid, peak, peak2, peak3, big_cloud, cloud, cloud2, cloud3, cloud4, fog, fog2, group_cloud, cloud_inter, cloud_inter2, cloud_inter3, lion;
	SDL_Rect fader, fademid;
	Animation inside, piston, screw;
	Animation* current_animation = nullptr;
	Animation* current_animation_2 = nullptr; 
	Animation* current_animation_3 = nullptr;
	float posx = 7000, posy = -480, grassy = 185;
	bool fade = true;
	float alpha_mid = 0, alpha_mid1 = 255, alpha_graph2 = 255, alpha_graph1 = 0, alpha_end = 0;
	int speed = 3, speedy = 0, animspeed = 0; 
	int framerateset = 0;
	int aux_time = 0;
	int increaser = 0, increaser_2 = 0;
	bool ship_flag1 = 0, ship_flag2 = 0, ship_flag3 = 0, ship_flag4 = 0, ship_flag5 = 0;
	bool flagship_1 = true;
	float bg_speed_default = 0.10f;
	float speed_screw = 0;
	int aux = 0;
	float speed_lion = 0;

	bool timer = true;
	int time_on_entry = 0, current_time = 0;

	bool god_mode = false;
};

#endif // __MODULESCENEFOREST_H__
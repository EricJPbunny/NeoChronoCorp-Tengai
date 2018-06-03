#ifndef __ENEMY_SHIPHEAD_H__
#define __ENEMY_SHIPHEAD_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_ShipHead :
	public Enemy
{
public:
	Enemy_ShipHead(int x, int y,int type);
	~Enemy_ShipHead();

	Collider* collider;
private:
	bool spawning;
	void Move();
	void Draw(SDL_Texture* sprites);
	SDL_Texture* boss_sprite;
	int current_time, time_on_entry;
	bool timer = true;
	int fire_rate= 90, shot_cd =0;
	int starter = 0;
	int  vectoy=0;
	enum shot_types {
		first_shot,
		second_shot,
	} current_shot = first_shot;
	shot_types last_shot;

	SDL_Rect bosscollider_1;
	SDL_Rect bosscollider_2;

	iPoint head_position;
	Animation spawn;
	Animation idle;
	Animation shoot;
	Path movement;
};

#endif#pragma once

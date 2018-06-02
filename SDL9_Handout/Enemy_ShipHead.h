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
	int fire_rate, shot_cd;

	SDL_Rect bosscollider_1;
	SDL_Rect bosscollider_2;

	iPoint head_position;
	Animation spawn;
	Animation idle;
	Animation shoot;
};

#endif#pragma once

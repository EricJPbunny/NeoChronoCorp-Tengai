#ifndef __ENEMY_TURRET_H__
#define __ENEMY_TURRET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Turret :
	public Enemy
{
public:
	Enemy_Turret(int x, int y, int type);
	~Enemy_Turret();

	Collider* collider;
	Path movement;

private:

	int type;
	void Move();
	void Draw(SDL_Texture* sprites);
	SDL_Texture* boss_sprite;
	iPoint head_position;

	Animation spawn, idle, death;
};

#endif

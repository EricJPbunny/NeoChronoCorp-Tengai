#ifndef __ENEMY_BUDA_H__
#define __ENEMY_BUDA_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Buda :
	public Enemy
{
public:
	Enemy_Buda(int x, int y, int type);
	~Enemy_Buda();

	Collider* collider;
	Path movement;

private:

	int type;
	void Move();
	void Draw(SDL_Texture* sprites);
	iPoint head_position;
	SDL_Texture* boss_sprite;

	Animation spawn, idle;
};

#endif

#ifndef __ENEMY_PALACE_H__
#define __ENEMY_PALACE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Palace :
	public Enemy
{
public:
	Enemy_Palace(int x, int y, int type);
	~Enemy_Palace();

	Collider* collider;
	Path movement;

private:

	int type;
	void Move();
	void Draw(SDL_Texture* sprites);
	SDL_Texture* boss_sprite;

	Animation spawn, idle;

};

#endif

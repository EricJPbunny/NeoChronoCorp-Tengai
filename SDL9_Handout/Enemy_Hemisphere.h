#ifndef __ENEMY_HEMISPHERE_H__
#define __ENEMY_HEMISPHERE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Hemisphere :
	public Enemy
{
public:
	Enemy_Hemisphere(int x, int y, int type);
	~Enemy_Hemisphere();

	Collider* collider;
	Path movement;

private:

	int type;
	void Move();
	void Draw(SDL_Texture* sprites);
	SDL_Texture* boss_sprite;

	Animation idle;
	
};

#endif

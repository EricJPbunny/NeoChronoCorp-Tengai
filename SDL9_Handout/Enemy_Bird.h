#ifndef __ENEMY_BIRD_H__
#define __ENEMY_BIRD_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Bird : public Enemy
{
private:

	iPoint originalposition;
	Animation idle;
	Path movement;

public:
	Enemy_Bird(int x, int y);

	void Move();
};

#endif // __ENEMY_BIRD_H__
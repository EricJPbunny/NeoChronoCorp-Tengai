#ifndef __ENEMY_COIN_H__
#define __ENEMY_COIN_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Coin : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint originalposition;
	Animation fly;
	Animation back;
	Path movement;
public:

	Enemy_Coin(int x, int y);

	void Move();
};

#endif // __ENEMY_COIN_H__

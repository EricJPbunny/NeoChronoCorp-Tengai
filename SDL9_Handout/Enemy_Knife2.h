#ifndef __ENEMY_KNIFE2_H__
#define __ENEMY_KNIFE2_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Knife2 : public Enemy
{
private:

	iPoint originalposition;
	Animation idle;

	Path movement;

public:
	Enemy_Knife2(int x, int y);

	void Move();
};

#endif // __ENEMY__H__

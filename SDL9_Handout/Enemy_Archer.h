#ifndef __ENEMY_ARCHER_H__
#define __ENEMY_ARCHER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Archer : public Enemy
{
private:

	iPoint originalposition;
	Animation idle;
	Animation up;
	Path movement;

public:
	Enemy_Archer(int x, int y);

	void Move();
};

#endif // __ENEMY__H__
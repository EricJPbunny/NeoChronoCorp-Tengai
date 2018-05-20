#ifndef __ENEMY_KNIFE_H__
#define __ENEMY_KNIFE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Knife : public Enemy
{
private:

	iPoint originalposition;
	Animation idle;

	Path diagonal;
	Path diagonalup;
	Path movement;
	int type;

public:
	Enemy_Knife(int x, int y, int type);

	void Move();
};

#endif // __ENEMY__H__
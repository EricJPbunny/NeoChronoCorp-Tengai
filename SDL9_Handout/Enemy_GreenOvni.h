#ifndef __ENEMY_GREENOVNI_H__
#define __ENEMY_GREENOVNI_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_GreenOvni : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint originalposition;
	Animation fly;
	Animation back;
	Path movement;

public:

	Enemy_GreenOvni(int x, int y, int type);

	void Move();
};

#endif // __ENEMY_GREENOVNI_H__
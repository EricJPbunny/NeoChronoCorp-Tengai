#ifndef __ENEMY_NINJA_H__
#define __ENEMY_NINJA_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Ninja : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint originalposition;
	
	Animation fly;
	Animation recharge;
	Animation armed;
	Animation lift;
	Animation run;
	Animation up;
	Animation stay;
	Path movement;
	int shootTimer = 0;
public:

	Enemy_Ninja(int x, int y, int type);

	void Move();
};

#endif // __ENEMY_GREENOVNI_H__

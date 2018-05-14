#ifndef __ENEMY_REDOVNI_H__
#define __ENEMY_REDOVNI_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RedOvni : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint originalposition;
	Animation fly;
	Animation back;
	Path movement;
public:

	Enemy_RedOvni(int x, int y, int type);

	void Move();
};

#endif // __ENEMY_REDOVNI_H__

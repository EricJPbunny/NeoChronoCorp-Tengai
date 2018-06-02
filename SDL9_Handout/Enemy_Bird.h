#ifndef __ENEMY_BIRD_H__
#define __ENEMY_BIRD_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Bird : public Enemy
{
private:

	iPoint originalposition;
	Animation idle;

	Animation shot;
	Animation shot2;
	Animation shot3;
	Animation shot4;
	Animation shot5;
	Animation shot6;

	Animation main;

	Path birddown;
	Path birdmov;
	Path birdup;

	int current_time, time_on_entry;
	bool timer = true;
	bool shooting = true;
	
	
	int type;

public:
	Enemy_Bird(int x, int y, int type);

	void Move();
};

#endif // __ENEMY_BIRD_H__
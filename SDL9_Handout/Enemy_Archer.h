#ifndef __ENEMY_ARCHER_H__
#define __ENEMY_ARCHER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Archer : public Enemy
{
private:

	iPoint originalposition;
	Animation idle;
	Animation sheathe;
	Animation sheathe1;
	Animation sheathe2;
	Animation sheathe3;
	Animation sheathe4;
	Animation sheathe5;
	Animation sheathe6;
	Animation sheathe7;
	Animation sheathe8;
	Animation sheathe9;
	Animation sheathe10;
	Animation sheathe11;
	Animation sheathe12;
	Animation up;
	Path movement;
	Path movementback;
	int type;
	int current_time, time_on_entry;
	bool timer = true;
	bool shooting = true;

public:
	Enemy_Archer(int x, int y, int type);

	void Move();
};

#endif // __ENEMY__H__
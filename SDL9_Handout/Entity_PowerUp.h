#ifndef __ENTITY_POWERUP_H__
#define __ENTITY_POWERUP_H__

#include "Enemy.h"
#include "Path.h"

class EntityPowerUp : public Enemy
{
private:
	iPoint originalposition;
	Animation iddle;
	Path movement;
public:

	EntityPowerUp(int x, int y, int type);

	void Move();
};

#endif // __ENEMY_GREENOVNI_H__
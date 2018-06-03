#ifndef __ENTITY_ULTI_H__
#define __ENTITY_ULTI_H__

#include "Enemy.h"
#include "Path.h"

class EntityUlti : public Enemy
{
private:
	iPoint originalposition;
	Animation iddle;
	Path movement;
public:

	EntityUlti(int x, int y, int type);

	void Move();
};

#endif // __ENTITY_ULTI_H__
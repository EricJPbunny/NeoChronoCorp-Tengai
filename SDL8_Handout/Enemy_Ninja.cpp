#include "Application.h"
#include "Enemy_Ninja.h"
#include "ModuleCollision.h"


Enemy_Ninja::Enemy_Ninja(int x, int y) :Enemy(x, y)
{
	fly.PushBack({ 19,117,28,37 });
	fly.speed = 0.2f;
	movement.PushBack({ 1.75f, 2.5f }, 80, &fly);

	stop.PushBack({ 66,127,28,28 });
	stop.PushBack({ 113,124,28,31 });
	stop.PushBack({ 158,113,30,42 });
	stop.speed = 0.2f;
	movement.PushBack({ 0.0f, 0.0f }, 40, &stop);

	animation = &fly;
	
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Ninja::Move()
{
	position = originalposition + movement.GetCurrentPosition(&animation);
	
}
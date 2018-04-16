#include "Application.h"
#include "Enemy_RedOvni.h"
#include "ModuleCollision.h"


Enemy_RedOvni::Enemy_RedOvni(int x, int y) :Enemy(x, y)
{
	fly.PushBack({ 16,60,30,30 });
	fly.PushBack({ 62,60,30,30 });
	fly.PushBack({ 110,60,30,30 });
	fly.PushBack({ 155,60,30,30 });

	fly.speed = 0.2f;

	movement.PushBack({ -0.2f, 1.3f }, 80);
	movement.PushBack({ 0.2f, -1.3f }, 80);
	animation = &fly;
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_RedOvni::Move()
{
	position = originalposition + movement.GetCurrentPosition();
}
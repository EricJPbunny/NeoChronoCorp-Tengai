#include "Application.h"
#include "Enemy_GreenOvni.h"
#include "ModuleCollision.h"


Enemy_GreenOvni::Enemy_GreenOvni(int x, int y):Enemy(x,y)
{
	fly.PushBack({ 14,16,30,30 });
	fly.PushBack({ 61,16,30,30 });
	fly.PushBack({ 107,16,30,30 });
	fly.PushBack({ 152,16,30,30 });
	fly.PushBack({ 152,16,30,30 });
	fly.speed = 0.2f;

	movement.PushBack({ -0.2f, 1.3f }, 80);
	movement.PushBack({ 0.2f, -1.3f }, 80);

	animation = &fly;
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_GreenOvni::Move()
{
	position = originalposition + movement.GetCurrentPosition();
}
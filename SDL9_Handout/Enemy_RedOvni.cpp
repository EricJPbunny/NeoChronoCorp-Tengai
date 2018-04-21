#include "Application.h"
#include "Enemy_RedOvni.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"


Enemy_RedOvni::Enemy_RedOvni(int x, int y) :Enemy(x, y)
{
	fly.PushBack({ 16,60,30,30 });
	fly.PushBack({ 62,60,30,30 });
	fly.PushBack({ 110,60,30,30 });
	fly.PushBack({ 155,60,30,30 });

	back.PushBack({ 14,16,30,30 });
	back.PushBack({ 61,16,30,30 });
	back.PushBack({ 107,16,30,30 });
	back.PushBack({ 152,16,30,30 });

	fly.speed = App->enemies->speed;

	movement.PushBack({ -0.1f, 0.0f }, 80);
	//movement.PushBack({ 1.0f, 0.0f }, 160, &back);
	animation = &fly;
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_RedOvni::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed();
	}
}
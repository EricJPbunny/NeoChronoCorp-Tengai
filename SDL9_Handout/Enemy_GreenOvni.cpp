#include "Application.h"
#include "Enemy_GreenOvni.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


Enemy_GreenOvni::Enemy_GreenOvni(int x, int y):Enemy(x,y)
{
	fly.PushBack({ 14,16,30,30 });
	fly.PushBack({ 61,16,30,30 });
	fly.PushBack({ 107,16,30,30 });
	fly.PushBack({ 152,16,30,30 });
	fly.speed = App->enemies->speed;

	back.PushBack({ 14,16,30,30 });
	back.PushBack({ 61,16,30,30 });
	back.PushBack({ 107,16,30,30 });
	back.PushBack({ 152,16,30,30 });
	

	movement.PushBack({ -0.1f, 0.0f }, 80, &fly);
	//movement.PushBack({ 1.0f, 0.0f }, 160, &back);

	animation = &fly;
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_GreenOvni::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed();
	}
}
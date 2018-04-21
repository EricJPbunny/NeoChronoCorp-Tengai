#include "Application.h"
#include "Entity_PowerUp.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


EntityPowerUp::EntityPowerUp(int x, int y) :Enemy(x, y)
{
	iddle.PushBack({ 14,16,30,30 });
	iddle.PushBack({ 61,16,30,30 });
	iddle.PushBack({ 107,16,30,30 });
	iddle.PushBack({ 152,16,30,30 });
	iddle.speed = App->enemies->speed;



	movement.PushBack({ -0.1f, 0.0f }, 80, &iddle);
	//movement.PushBack({ 1.0f, 0.0f }, 160, &back);

	animation = &iddle;
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_GreenOvni::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed();
	}
}
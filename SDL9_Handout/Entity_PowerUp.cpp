#include "Application.h"
#include "Entity_PowerUp.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


EntityPowerUp::EntityPowerUp(int x, int y, int type) :Enemy(x, y, type)
{
	iddle.PushBack({ 215,127,31,22 });
	iddle.PushBack({ 246,127,31,22 });
	iddle.PushBack({ 277,127,31,21 });
	iddle.PushBack({ 308,127,31,20 });
	iddle.PushBack({ 339,127,31,20 });

	iddle.PushBack({ 215,149,31,20 });
	iddle.PushBack({ 246,149,31,20 });
	iddle.PushBack({ 277,149,31,20 });
	iddle.PushBack({ 308,149,31,20 });
	iddle.PushBack({ 339,149,31,20 });

	iddle.PushBack({ 215,169,31,21 });
	iddle.PushBack({ 246,169,31,21 });
	iddle.PushBack({ 277,169,31,21 });
	iddle.PushBack({ 308,169,31,21 });
	iddle.PushBack({ 339,169,31,20 });

	iddle.PushBack({ 215,190,31,21 });
	iddle.speed = App->enemies->speed;

	movement.PushBack({ -0.1f, 0.0f }, 80, &iddle);
	movement.PushBack({ 1.0f, 0.0f }, 160, &iddle);

	animation = &iddle;
	collider = App->collision->AddCollider({ 0, 0, 24, 20 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void EntityPowerUp::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed();
	}
}
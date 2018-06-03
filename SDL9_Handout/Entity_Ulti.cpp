#include "Application.h"
#include "Entity_Ulti.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


EntityUlti::EntityUlti(int x, int y, int type) :Enemy(x, y, type)
{
	iddle.PushBack({ 325,422,31,22 });
	iddle.PushBack({ 360,422,31,22 });
	iddle.PushBack({ 394,422,31,22 });
	iddle.PushBack({ 428,422,31,22 });

	iddle.PushBack({ 268,448,31,22 });
	iddle.PushBack({ 303,448,31,22 });
	iddle.PushBack({ 338,448,31,22 });
	iddle.PushBack({ 371,448,31,22 });
	iddle.PushBack({ 405,448,31,22 });

	iddle.PushBack({ 270,473,31,22 });
	
	iddle.speed = App->enemies->speed;

	movement.PushBack({ -0.1f, 0.0f }, 80, &iddle);
	movement.PushBack({ 1.0f, 0.0f }, 160, &iddle);

	animation = &iddle;
	collider = App->collision->AddCollider({ 0, 0, 24, 20 }, COLLIDER_TYPE::COLLIDER_ENTITY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void EntityUlti::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed();
	}
}
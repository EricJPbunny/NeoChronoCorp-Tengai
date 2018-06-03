#include "Application.h"
#include "Entity_Ulti.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


EntityUlti::EntityUlti(int x, int y, int type) :Enemy(x, y, type)
{
	iddle.PushBack({ 65,102,31,21 });
	iddle.PushBack({ 100,102,31,20 });
	iddle.PushBack({ 134,102,31,20 });
	iddle.PushBack({ 168,102,31,20 });
	iddle.PushBack({ 8,128,31,20 });
	iddle.PushBack({ 43,130,31,20 });
	iddle.PushBack({ 78,129,31,20 });
	iddle.PushBack({ 111,129,31,20 });
	iddle.PushBack({ 10,153,31,21 });
	
	iddle.speed = App->enemies->speed;

	movement.PushBack({ -0.1f, 0.0f }, 80, &iddle);
	movement.PushBack({ 1.0f, 0.0f }, 160, &iddle);

	animation = &iddle;
	collider = App->collision->AddCollider({ 0, 0, 24, 20 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void EntityUlti::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed();
	}
}
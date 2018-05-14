#include "Application.h"
#include "Enemy_Bird.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


Enemy_Bird::Enemy_Bird(int x, int y, int type) :Enemy(x, y, type)
{
	idle.PushBack({ 11,90,40,37 });
	idle.PushBack({ 55,88,40,37 });
	idle.speed = 0.2f;

	shot.PushBack({ 100,87,40,37 });
	shot.PushBack({ 151,84,40,37 });
	shot.PushBack({ 201,82,40,37 });
	shot.PushBack({ 248,80,40,37 });
	shot.PushBack({ 290,79,40,37 });
	shot.PushBack({ 336,80,40,37 });
	shot.PushBack({ 377,80,40,37 });
	shot.speed = 0.2f;
	
	movement.PushBack({ 0.0f, 0.0f }, 200, &idle);
	movement.PushBack({ 1.0f, 0.0f }, 100, &shot);
	movement.PushBack({ 0.0f, -1.0f }, 300, &shot);

	

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Bird::Move()
{
	
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed(&animation);
	}
}
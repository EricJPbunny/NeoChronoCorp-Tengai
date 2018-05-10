#include "Application.h"
#include "Enemy_Knife.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


Enemy_Knife::Enemy_Knife(int x, int y):Enemy(x,y)
{
	idle.PushBack({ 6,50,32,30 });
	idle.PushBack({ 50,49,32,30 });
	idle.PushBack({ 91,49,32,30 });
	idle.PushBack({ 135,49,32,30 });
	idle.PushBack({ 182,50,32,30 });
	idle.PushBack({ 229,49,32,30 });
	idle.PushBack({ 274,48,32,30 });
	idle.PushBack({ 325,49,32,30 });
	idle.speed = 0.2f;
	
	movement.PushBack({ 0.0f, 0.0f }, 90, &idle);

	//collider = App->collision->AddCollider({ 0, 0, 10, 10 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Knife::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed(&animation);
	}
}
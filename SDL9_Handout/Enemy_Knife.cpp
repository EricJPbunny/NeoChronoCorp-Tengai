#include "Application.h"
#include "Enemy_Knife.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


Enemy_Knife::Enemy_Knife(int x, int y):Enemy(x,y)
{
	idle.PushBack({});
	

	movement.PushBack({ -0.1f, 0.0f }, 90);
	movement.PushBack({ 3.7f, 0.0f }, 1000);

	
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Knife::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed();
	}
}
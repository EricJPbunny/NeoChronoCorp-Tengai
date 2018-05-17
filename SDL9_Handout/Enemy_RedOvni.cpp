#include "Application.h"
#include "Enemy_RedOvni.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"


Enemy_RedOvni::Enemy_RedOvni(int x, int y, int type) :Enemy(x, y, type)
{
	fly.PushBack({ 196,16,40,30 });
	fly.PushBack({ 242,16,40,30 });
	fly.PushBack({ 290,16,40,30 });
	fly.PushBack({ 335,16,40,30 });
	

	back.PushBack({ 196,16,40,30 });
	back.PushBack({ 242,16,40,30 });
	back.PushBack({ 290,16,40,30 });
	back.PushBack({ 335,16,40,30 });

	fly.speed = App->enemies->speed;

	movement.PushBack({ -0.7f, 0.0f }, 90,&fly);
	
	animation = &fly;
	collider = App->collision->AddCollider({ 0, 0, 40, 30 }, COLLIDER_TYPE::COLLIDER_REDOVNI, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_RedOvni::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed();
	}
}
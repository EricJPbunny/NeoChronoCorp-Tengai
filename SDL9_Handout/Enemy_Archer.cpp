#include "Application.h"
#include "Enemy_Archer.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"


Enemy_Archer::Enemy_Archer(int x, int y, int type) :Enemy(x, y, type)
{
	idle.PushBack({ 10,203,44,48 });
	idle.PushBack({ 61,203,44,48 });
	idle.PushBack({ 111,203,44,48 });
	idle.PushBack({ 165,203,44,48 });
	idle.PushBack({ 394,201,44,48 });
	idle.PushBack({ 280,203,44,48 });
	idle.PushBack({ 343,203,44,48 });
	idle.PushBack({ 27,260,44,48 });
	idle.PushBack({ 93,260,44,48 });
	idle.speed = 0.01f;

	sheathe.PushBack({ 150,258,44,48 });
	sheathe.PushBack({ 207,257,44,48 });
	sheathe.PushBack({ 269,257,44,48 });
	sheathe.PushBack({ 332,257,44,48 });
	sheathe.PushBack({ 27,260,44,48 });
	sheathe.PushBack({ 93,260,44,48 });
	sheathe.PushBack({ 343,203,44,48 });
	sheathe.PushBack({ 280,203,44,48 });
	sheathe.PushBack({ 394,201,44,48 });
	sheathe.PushBack({ 165,203,44,48 });
	sheathe.PushBack({ 111,203,44,48 });
	sheathe.PushBack({ 61,203,44,48 });
	sheathe.PushBack({ 10,203,44,48 });
	sheathe.speed = 0.2f;

	up.PushBack({ 10,203,44,48 });
	up.speed = 0.2f;

	//Movement
	movement.PushBack({ -1.3f, 0.0f }, 40, &idle);
	movement.PushBack({ 1.0f, 0.0f }, 39, &sheathe);
	movement.PushBack({ 1.0f, -1.5f }, 600, &up);
	
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &idle;
	
	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Archer::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed(&animation);
	}
}
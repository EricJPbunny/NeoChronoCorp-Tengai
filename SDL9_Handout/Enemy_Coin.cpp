#include "Application.h"
#include "Enemy_Coin.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"


Enemy_Coin::Enemy_Coin(int x, int y) :Enemy(x, y)
{
	up.PushBack({ 20,415,16,16 });
	up.PushBack({ 40,415,16,16 });
	up.PushBack({ 60,415,16,16 });
	up.PushBack({ 78,415,16,16 });
	up.PushBack({ 97,415,16,16 });
	up.PushBack({ 113,415,16,16 });
	up.PushBack({ 132,415,16,16 });
	up.PushBack({ 147,415,16,16 });
	up.PushBack({ 164,415,16,16 });
	up.PushBack({ 182,415,16,16 });
	up.PushBack({ 201,415,16,16 });
	up.PushBack({ 219,415,16,16 });
	up.PushBack({ 236,415,16,16 });
	up.PushBack({ 255,415,16,16 });
	up.PushBack({ 274,415,16,16 });
	up.PushBack({ 295,415,16,16 });

	
	down.PushBack({ 20,415,16,16 });
	down.PushBack({ 40,415,16,16 });
	down.PushBack({ 60,415,16,16 });
	down.PushBack({ 78,415,16,16 });
	down.PushBack({ 97,415,16,16 });
	down.PushBack({ 113,415,16,16 });
	down.PushBack({ 132,415,16,16 });
	down.PushBack({ 147,415,16,16 });
	down.PushBack({ 164,415,16,16 });
	down.PushBack({ 182,415,16,16 });
	down.PushBack({ 201,415,16,16 });
	down.PushBack({ 219,415,16,16 });
	down.PushBack({ 236,415,16,16 });
	down.PushBack({ 255,415,16,16 });
	down.PushBack({ 274,415,16,16 });
	down.PushBack({ 295,415,16,16 });
	
	up.speed = App->enemies->speed;

	movement.PushBack({ 1.75f, -3.0f }, 58, &up);
	movement.PushBack({ 1.75f, 3.0f }, 58, &down);
	animation = &up;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_COIN, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Coin::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed(&animation);
	}

}
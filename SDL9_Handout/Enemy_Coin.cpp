#include "Application.h"
#include "Enemy_Coin.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"


Enemy_Coin::Enemy_Coin(int x, int y) :Enemy(x, y)
{
	fly.PushBack({ 20,415,16,16 });
	fly.PushBack({ 40,415,16,16 });
	fly.PushBack({ 60,415,16,16 });
	fly.PushBack({ 78,415,16,16 });
	fly.PushBack({ 97,415,16,16 });
	fly.PushBack({ 113,415,16,16 });
	fly.PushBack({ 132,415,16,16 });
	fly.PushBack({ 147,415,16,16 });
	fly.PushBack({ 164,415,16,16 });
	fly.PushBack({ 182,415,16,16 });
	fly.PushBack({ 201,415,16,16 });
	fly.PushBack({ 219,415,16,16 });
	fly.PushBack({ 236,415,16,16 });
	fly.PushBack({ 255,415,16,16 });
	fly.PushBack({ 274,415,16,16 });
	fly.PushBack({ 295,415,16,16 });
	
	fly.speed = App->enemies->speed;

	movement.PushBack({ 1.75f, 3.0f }, 58, &fly);
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Coin::Move()
{
	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed(&animation);
	}

}
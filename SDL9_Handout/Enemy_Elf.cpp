#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Enemy_Elf.h"

Enemy_Elf::Enemy_Elf(int x, int y, int type) :Enemy(x, y, type)
{
	fire_rate = 90;
	boss_sprite = App->textures->Load("assets/sprite/Tijeras_Boss.png");

	previous.PushBack({ 42, 736, 32, 35 });
	previous.PushBack({ 80, 736, 32, 35 });
	previous.PushBack({ 121, 736, 32, 35 });
	previous.PushBack({ 165, 736, 32, 35 });
	previous.PushBack({ 207, 736, 32, 35 });
	previous.speed = 0.08f;



	spawn.PushBack({ 18, 305, 104, 89 });
	spawn.PushBack({ 154, 305, 104, 89 });
	spawn.PushBack({ 289, 305, 104, 89 });
	spawn.PushBack({ 435, 305, 104, 89 });
	spawn.speed = 0.1f;


	stay.PushBack({ 1637, 19, 75, 89});
	stay.speed = 0.09f;
	stay2.PushBack({ 1553, 19, 42, 87});
	stay2.speed = 0.09f;


	idle.PushBack({ 13, 23, 91, 74 });
	idle.PushBack({ 117, 23, 91, 74 });
	idle.PushBack({ 223, 23, 91, 74 });
	idle.PushBack({ 324, 23, 91, 74 });
	idle.PushBack({ 422, 23, 91, 74 });
	idle.PushBack({ 520, 23, 91, 74 });
	
	idle.speed = 0.1f;

	back.PushBack({ 1229, 28, 81, 71 });
	back.speed = 0.1f;

	back2.PushBack({ 1330, 28, 81, 71 });
	back2.speed = 0.1f;

	back3.PushBack({ 1224, 28, 81, 71 });
	back3.speed = 0.1f;
	
	back4.PushBack({ 119, 24, 83, 71 });
	back4.speed = 0.1f;

	

	movement.PushBack({ 1.0f, 0.0f  },15, &previous);
	movement.PushBack({ -0.5f, 0.0f }, 600, &spawn);
	movement.PushBack({ 1.0f, 0.0f }, 50, &stay);
	movement.PushBack({ 1.0f, 0.0f }, 50, &stay2);
	movement.PushBack({ 1.0f, 0.0f }, 250, &idle);
	movement.PushBack({ 1.0f, 0.0f }, 3, &back);
	movement.PushBack({ 1.0f, 0.0f }, 3, &back2);
	movement.PushBack({ 1.0f, 0.0f }, 3, &back3);
	movement.PushBack({ 1.0f, 0.0f }, 3, &back4);
	

	
	animation = &previous;
	this->type = type;
}


Enemy_Elf::~Enemy_Elf()
{
	App->textures->Unload(boss_sprite);

}


void Enemy_Elf::Move()
{
	if (previous.Finished())
	{
		animation = &spawn;
	}
	if (spawn.Finished())
	{
		animation = &stay;
	}
	if (stay.Finished())
	{
		animation = &stay2;
	}
	if (stay2.Finished())
	{
		animation = &idle;
	}
	if (idle.Finished())
	{
		animation = &back;
	}
	if (back.Finished())
	{
		animation = &back2;
	}
	if (back2.Finished())
	{
		animation = &back3;
	}
	if (back3.Finished())
	{
		animation = &back4;
	}

}

void Enemy_Elf::Draw(SDL_Texture* sprites) {
	Enemy::Draw(boss_sprite);
}
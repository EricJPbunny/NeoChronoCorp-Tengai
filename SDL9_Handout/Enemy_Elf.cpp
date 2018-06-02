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

	previous.PushBack({ 18, 305, 104, 89 });
	previous.PushBack({ 154, 305, 104, 89 });
	previous.PushBack({ 289, 305, 104, 89 });
	previous.PushBack({ 435, 305, 104, 89 });
	spawn.speed = 0.02f;



	spawn.PushBack({ 18, 305, 104, 89 });
	spawn.PushBack({ 154, 305, 104, 89 });
	spawn.PushBack({ 289, 305, 104, 89 });
	spawn.PushBack({ 435, 305, 104, 89 });
	spawn.speed = 0.02f;


	stay.PushBack({ 1637, 20, 75, 88});
	stay.speed = 0.02f;


	idle.PushBack({ 13, 23, 91, 74 });
	idle.PushBack({ 117, 23, 91, 74 });
	idle.PushBack({ 223, 23, 91, 74 });
	idle.PushBack({ 324, 23, 91, 74 });
	idle.PushBack({ 422, 23, 91, 74 });
	idle.PushBack({ 520, 23, 91, 74 });
	idle.PushBack({ 537, 23, 91, 74 });
	
	idle.speed = 0.02f;
	
	animation = &spawn;

	movement.PushBack({ -0.5,0 }, 50, &spawn);
	movement.PushBack({ 1,0 }, 50, &stay);
	

	this->type = type;
}


Enemy_Elf::~Enemy_Elf()
{
	App->textures->Unload(boss_sprite);

}


void Enemy_Elf::Move()
{
	if (spawn.Finished())
	{
		animation = &stay;
	}

}

void Enemy_Elf::Draw(SDL_Texture* sprites) {
	Enemy::Draw(boss_sprite);
}
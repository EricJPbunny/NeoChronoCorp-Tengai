#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Enemy_Palace.h"

Enemy_Palace::Enemy_Palace(int x, int y, int type) :Enemy(x, y,type)
{

	boss_sprite = App->textures->Load("assets/sprite/boss/palace.png");

	spawn.PushBack({ 0,0,81,84 });
	spawn.PushBack({ 72,0,81,84 });
	spawn.PushBack({ 151,0,81,84 });
	spawn.PushBack({ 231,0,81,84 });
	spawn.PushBack({ 318,0,81,84 });
	spawn.PushBack({ 405,0,81,84 });
	spawn.PushBack({ 1,170,81,70 });
	spawn.PushBack({ 82,170,81,70 });
	spawn.speed = 0.20f;

	idle.PushBack({ 168,170,81,70 });
	idle.PushBack({ 416,170,81,70 });
	idle.PushBack({ 332,170,81,70 });
	idle.PushBack({ 249,170,81,70 });
	idle.speed = 0.20f;

	animation = &spawn;

	collider = App->collision->AddCollider({ 0, 0, 30, 50 }, COLLIDER_TYPE::COLLIDER_ELF, (Module*)App->enemies);

	this->type = type;

}


Enemy_Palace::~Enemy_Palace()
{
	App->textures->Unload(boss_sprite);
	
}

void Enemy_Palace::Move()
{
	if (spawn.Finished())
	{
		animation = &idle;
	}
}

void Enemy_Palace::Draw(SDL_Texture* sprites)
{
	Enemy::Draw(boss_sprite);
}

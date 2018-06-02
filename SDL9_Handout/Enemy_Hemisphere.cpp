#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Enemy_Hemisphere.h"

Enemy_Hemisphere::Enemy_Hemisphere(int x, int y, int type) :Enemy(x, y,type)
{

	boss_sprite = App->textures->Load("assets/sprite/boss/Boss_Hemisphere.png");

	idle.PushBack({ 168,170,81,70 });
	idle.PushBack({ 416,170,81,70 });
	idle.PushBack({ 332,170,81,70 });
	idle.PushBack({ 249,170,81,70 });
	idle.speed = 0.20f;

	animation = &idle;

	this->type = type;

}


Enemy_Hemisphere::~Enemy_Hemisphere()
{
	App->textures->Unload(boss_sprite);
	
}

void Enemy_Hemisphere::Move()
{

}

void Enemy_Hemisphere::Draw(SDL_Texture* sprites)
{
	Enemy::Draw(boss_sprite);
}

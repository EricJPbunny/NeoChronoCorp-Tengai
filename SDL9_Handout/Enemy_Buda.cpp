#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Enemy_Buda.h"
#include "ModuleUI.h"

Enemy_Buda::Enemy_Buda(int x, int y, int type) :Enemy(x, y,type)
{

	boss_sprite = App->textures->Load("assets/sprite/boss/Budah.png");

	spawn.PushBack({ 9,117,71,148 });
	spawn.PushBack({ 133,116,71,148 });
	spawn.PushBack({ 256,115,71,148 });
	spawn.PushBack({ 367,115,71,148 });
	spawn.PushBack({ 479,115,71,148 });
	spawn.PushBack({ 596,115,71,148 });
	spawn.PushBack({ 711,115,71,148 });
	spawn.PushBack({ 11,281,71,148 });
	spawn.PushBack({ 129,281,71,148 });
	spawn.speed = 0.20f;

	idle.PushBack({ 245,281,71,148 });
	idle.speed = 0.20f;

	animation = &spawn;

	movement.PushBack({ 0.0f, 0.0f }, 90, &spawn);
	movement.PushBack({ 1.0f, 0.0f }, 9999, &idle);

	this->type = type;
	head_position.x = x;
	head_position.y = y;

}


Enemy_Buda::~Enemy_Buda()
{
	App->textures->Unload(boss_sprite);
	
}

void Enemy_Buda::Move()
{
	if (spawn.Finished())
	{
		animation = &idle;
	}
	if (App->ui->enemies_movement) {
		position = head_position + movement.GetCurrentSpeed(&animation);
	}
}

void Enemy_Buda::Draw(SDL_Texture* sprites)
{
	Enemy::Draw(boss_sprite);
}

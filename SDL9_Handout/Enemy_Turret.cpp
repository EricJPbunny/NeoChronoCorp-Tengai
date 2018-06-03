#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "Enemy_Turret.h"

Enemy_Turret::Enemy_Turret(int x, int y, int type) :Enemy(x, y,type)
{

	boss_sprite = App->textures->Load("assets/sprite/boss/Turret.png");

	spawn.PushBack({ 2,73,36,39 });
	spawn.PushBack({ 40,73,36,39 });
	spawn.PushBack({ 77,73,36,39 });
	spawn.speed = 0.20f;

	idle.PushBack({ 119,73,36,39 });
	idle.PushBack({ 153,73,36,39 });
	idle.PushBack({ 191,73,36,39 });
	idle.PushBack({ 229,73,36,39 });
	idle.PushBack({ 267,73,36,39 });
	idle.PushBack({ 305,73,36,39 });
	idle.speed = 0.20f;

	death.PushBack({ 315,376,81,20 });
	death.loop = true;

	movement.PushBack({ 0.0f, 0.0f }, 160, &spawn);
	movement.PushBack({ 1.0f, 0.0f }, 9999, &idle);

	animation = &spawn;
	head_position.x = x;
	head_position.y = y;
	this->type = type;
	collider = App->collision->AddCollider({ 0, 0, 30, 50 }, COLLIDER_TYPE::COLLIDER_TURRET, (Module*)App->enemies);

}


Enemy_Turret::~Enemy_Turret()
{
	App->textures->Unload(boss_sprite);
	
}

void Enemy_Turret::Move()
{
	if (spawn.Finished())
	{
		animation = &idle;
	}
	if (App->ui->enemies_movement) {
		position = head_position + movement.GetCurrentSpeed(&animation);
	}
}

void Enemy_Turret::Draw(SDL_Texture* sprites)
{
	Enemy::Draw(boss_sprite);
}

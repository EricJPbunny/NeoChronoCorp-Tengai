#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Enemy_ShipHead.h"

Enemy_ShipHead::Enemy_ShipHead(int x, int y,int type) :Enemy(x, y,type)
{
	fire_rate = 90;
	spawn.PushBack({ 0, 0, 93, 90 });
	spawn.PushBack({ 105,0,101,103 });
	spawn.PushBack({ 216,0,109,114 });
	spawn.PushBack({ 339,0,113,127 });
	spawn.PushBack({ 0,141,110,128 });
	spawn.speed = 0.02f;

	boss_sprite = App->textures->Load("assets/sprite/spritesheet_head_boss.png");
	animation = &spawn;
	head_position.x = x;
	head_position.y = y;
}


Enemy_ShipHead::~Enemy_ShipHead()
{
	App->textures->Unload(boss_sprite);
	
}


void Enemy_ShipHead::Shoot()
{
	if (shot_cd == 0) 
	{
		animation = &shoot;
		shot_cd = fire_rate;
	}
	else shot_cd++;
		
}

void Enemy_ShipHead::Draw(SDL_Texture* sprites) {
	Enemy::Draw(boss_sprite);
}
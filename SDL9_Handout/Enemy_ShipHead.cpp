#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayer3.h"
#include "Enemy_ShipHead.h"
#include "SDL\include\SDL_timer.h"


Enemy_ShipHead::Enemy_ShipHead(int x, int y,int type) :Enemy(x, y,type)
{
	spawn.PushBack({ 0, 0, 93, 90 });
	spawn.PushBack({ 105,0,101,103 });
	spawn.PushBack({ 216,0,109,114 });
	spawn.PushBack({ 0,141,110,128 });
	spawn.PushBack({ 339,0,113,127 });
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


void Enemy_ShipHead::Move()
{
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		LOG("DEBUGER");
	}
	if (spawn.Finished())
	{
		animation = &idle;
	}
	if (shot_cd == 0) {
		int  vectoy;
		float magnitude;

		switch (current_shot) {
		case shot_types::first_shot:
			
			
			if (App->player2->position.y < 100) 
			{
				vectoy = -1;
			}
			if (App->player2->position.y > 150)
			{
				vectoy = 1;
			}

			//App->particles->shipHead_shoot.speed.y = vectoy;

			App->particles->AddParticle(App->particles->shipHead_shoot, position.x + 22, position.y + 78, COLLIDER_ENEMY_SHOT);
			if (last_shot == second_shot) current_shot = first_shot;
			else current_shot = first_shot;

			last_shot = first_shot;
			break;
		case shot_types::second_shot:
			
			last_shot = second_shot;
			current_shot = first_shot;
			break;
		}
		shot_cd = fire_rate;
	}
	else shot_cd--;

	
}

void Enemy_ShipHead::Draw(SDL_Texture* sprites) {
	Enemy::Draw(boss_sprite);
}
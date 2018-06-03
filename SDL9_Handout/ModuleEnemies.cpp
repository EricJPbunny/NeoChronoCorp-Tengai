#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayer3.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleSceneAir.h"
#include "Enemy.h"
#include "Enemy_Archer.h"
#include "Enemy_Bird.h"
#include "Enemy_Knife.h"
#include "Enemy_Turret.h"
#include "Enemy_Buda.h"
#include "Enemy_Palace.h"
#include "Enemy_Elf.h"
#include "Enemy_Hemisphere.h"
#include "Entity_PowerUp.h"
#include "Enemy_Coin.h"
#include "Entity_Ulti.h"
#include "time.h"
#include "stdlib.h"

#include "SDL\include\SDL_timer.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("assets/sprite/enemies.png");
	puSprites = App->textures->Load("assets/sprite/enemies.png");

	fx_death = App->audio->LoadEffect("assets/audio/enemy_death.wav");
	s_power_down = App->audio->LoadEffect("assets/audio/sho_lvl_down.wav");
	j_power_down = App->audio->LoadEffect("assets/audio/junis_lvl_down.wav");
	catch_bomb = App->audio->LoadEffect("assets/audio/catch_bomb.wav");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Move();

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if(enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->audio->UnloadFx(j_power_down);
	App->audio->UnloadFx(s_power_down);
	App->audio->UnloadFx(fx_death);
	App->textures->Unload(sprites);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, int path_type)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].path_type = path_type;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(;enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
			case ENEMY_TYPES::GREENOVNI:
				enemies[i] = new Enemy_GreenOvni(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::REDOVNI:
				enemies[i] = new Enemy_RedOvni(info.x, info.y ,info.path_type);
				break;
			case ENEMY_TYPES::NINJA:
				enemies[i] = new Enemy_Ninja(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::POWERUP:
				enemies[i] = new EntityPowerUp(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::COIN:
				enemies[i] = new Enemy_Coin(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::ARCHER:
				enemies[i] = new Enemy_Archer(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::BIRD:
				enemies[i] = new Enemy_Bird(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::KNIFE:
				enemies[i] = new Enemy_Knife(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::BOSSHEAD:
				enemies[i] = new Enemy_ShipHead(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::TURRET:
				enemies[i] = new Enemy_Turret(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::PALACE:
				enemies[i] = new Enemy_Palace(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::BUDA:
				enemies[i] = new Enemy_Buda(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::ELF:
				enemies[i] = new Enemy_Elf(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::HEMISPHERE:
				enemies[i] = new Enemy_Hemisphere(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::ULTI:
				enemies[i] = new EntityUlti(info.x, info.y, info.path_type);
				break;
			
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	float speed = App->scene_air->speed / SCREEN_SIZE;
	
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{

			//Player collides w enemies
			if (c2->type == COLLIDER_TYPE::COLLIDER_HITBOX && c1->type == COLLIDER_TYPE::COLLIDER_ENEMY) {
				if (c2 == App->player3->hitbox) {
					if (timer) {
						time_on_entry = SDL_GetTicks();
						timer = false;
					}
					current_time = SDL_GetTicks() - time_on_entry;
					if (current_time > 600) {
						if (App->player3->power_up > 0) {
							App->particles->power_down.speed.x = speed;
							App->particles->power_down.speed.y = -2;
							App->particles->AddParticle(App->particles->power_down, App->player->position.x, App->player->position.y);
						}
						App->player3->power_up--;
						timer = true;
					}
					App->audio->PlaySoundEffects(j_power_down);
					App->player3->spin_pos = true;
					App->player3->state = SPIN_3;
				}
				if (c2 == App->player2->hitbox) {
					if (timer_2) {
						time_on_entry_2 = SDL_GetTicks();
						timer_2 = false;
					}
					current_time_2 = SDL_GetTicks() - time_on_entry_2;
					if (current_time_2 > 600) {
						if (App->player2->power_up > 0) {
							App->particles->power_down.speed.x = speed;
							App->particles->power_down.speed.y = -2;
							App->particles->AddParticle(App->particles->power_down, App->player2->position.x, App->player2->position.y);
						}
						App->player2->power_up--;
						timer_2 = true;
					}
					App->audio->PlaySoundEffects(s_power_down);
					App->player2->spin_pos = true;
					App->player2->state = SPIN_2;
				}
			}

			//Kill Green Ovni
			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2 || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)) {

				num_ovni++;

				App->audio->PlaySoundEffects(fx_death);
				App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

				if (num_ovni >= 4) {
					AddEnemy(ENEMY_TYPES::COIN, enemies[i]->position.x, enemies[i]->position.y);
					num_ovni = 0;
				}
				delete enemies[i];
				enemies[i] = nullptr;

				if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT)
				{
					App->ui->score_koyori += 200;
				}
				if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2)
				{
					App->ui->score_sho += 200;
				}
				if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)
				{
					App->ui->score_junis += 200;
				}

			}
			//Coin
			if (c2->type == COLLIDER_TYPE::COLLIDER_HITBOX  && c1->type == COLLIDER_TYPE::COLLIDER_COIN) {
				srand(time(NULL));
				typeofcoin = rand() % 6;

				switch (typeofcoin) {
				case 0:
					coin_type = App->particles->coin_100;
					if (c2 == App->player->hitbox) {
						App->ui->score_koyori += 100;
						pos = App->player->position;
					}
					if (c2 == App->player2->hitbox) {
						App->ui->score_sho += 100;
						pos = App->player2->position;
					}
					if (c2 == App->player3->hitbox) {
						App->ui->score_junis += 100;
						pos = App->player3->position;
					}
					break;

				case 1:
					coin_type = App->particles->coin_200;
					if (c2 == App->player->hitbox) {
						App->ui->score_koyori += 200;
						pos = App->player->position;
					}
					if (c2 == App->player2->hitbox) {
						App->ui->score_sho += 200;
						pos = App->player2->position;
					}
					if (c2 == App->player3->hitbox) {
						App->ui->score_junis += 200;
						pos = App->player3->position;
					}
					break;

				case 2:
					coin_type = App->particles->coin_500;
					if (c2 == App->player->hitbox) {
						App->ui->score_koyori += 500;
						pos = App->player->position;
					}
					if (c2 == App->player2->hitbox) {
						App->ui->score_sho += 500;
						pos = App->player2->position;
					}
					if (c2 == App->player3->hitbox) {
						App->ui->score_junis += 500;
						pos = App->player3->position;
					}
					break;

				case 3:
					coin_type = App->particles->coin_1000;
					if (c2 == App->player->hitbox) {
						App->ui->score_koyori += 1000;
						pos = App->player->position;
					}
					if (c2 == App->player2->hitbox) {
						App->ui->score_sho += 1000;
						pos = App->player2->position;
					}
					if (c2 == App->player3->hitbox) {
						App->ui->score_junis += 1000;
						pos = App->player3->position;
					}
					break;

				case 4:
					coin_type = App->particles->coin_2000;
					if (c2 == App->player->hitbox) {
						App->ui->score_koyori += 2000;
						pos = App->player->position;
					}
					if (c2 == App->player2->hitbox) {
						App->ui->score_sho += 2000;
						pos = App->player2->position;
					}
					if (c2 == App->player3->hitbox) {
						App->ui->score_junis += 2000;
						pos = App->player3->position;
					}
					break;

				case 5:
					coin_type = App->particles->coin_4000;
					if (c2 == App->player->hitbox) {
						App->ui->score_koyori += 4000;
						pos = App->player->position;
					}
					if (c2 == App->player2->hitbox) {
						App->ui->score_sho += 4000;
						pos = App->player2->position;
					}
					if (c2 == App->player3->hitbox) {
						App->ui->score_junis += 4000;
						pos = App->player3->position;
					}
					break;

				}

				coin_type.speed.x = speed;
				coin_type.speed.y = -2;
				App->particles->AddParticle(coin_type, pos.x, pos.y, COLLIDER_NONE, PARTICLE_COIN);
				delete enemies[i];
				enemies[i] = nullptr;

			}

			//Power Ups
			if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER  && c1->type == COLLIDER_TYPE::COLLIDER_POWER_UP) {
				if (c2 == App->player->coll) {
					if (App->player->power_up < 4) {
						App->particles->power_up.speed.x = speed;
						App->particles->power_up.speed.y = -2;
						App->particles->AddParticle(App->particles->power_up, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_POWER_UP_KOYORI);
						App->player->power_up++;
					}
					else {
						App->particles->coin_2000.speed.x = speed;
						App->particles->coin_2000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_2000, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_koyori += 2000;
					}
				}
				if (c2 == App->player2->coll) {
					if (App->player2->power_up < 4) {
						App->particles->power_up.speed.x = speed;
						App->particles->power_up.speed.y = -2;
						App->particles->AddParticle(App->particles->power_up, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_POWER_UP_SHO);
						App->player2->power_up++;
					}
					else {
						App->particles->coin_2000.speed.x = speed;
						App->particles->coin_2000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_2000, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_sho += 2000;
					}
				}
				if (c2 == App->player3->coll) {
					if (App->player3->power_up < 4) {
						App->particles->power_up.speed.x = speed;
						App->particles->power_up.speed.y = -2;
						App->particles->AddParticle(App->particles->power_up, App->player3->position.x, App->player3->position.y, COLLIDER_NONE, PARTICLE_POWER_UP_JUNIS);
						App->player3->power_up++;
					}
					else {
						App->particles->coin_2000.speed.x = speed;
						App->particles->coin_2000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_2000, App->player3->position.x, App->player3->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_junis += 2000;
					}
				}
				delete enemies[i];
				enemies[i] = nullptr;
			}

			//Kill ninja
			if (c1->type == COLLIDER_TYPE::COLLIDER_NINJA && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2 || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)) {
				ninja_life++;
				if (ninja_life == 1) {
					App->particles->AddParticle(App->particles->spark, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->spark.speed.x = speed;
				}
				if (ninja_life == 2) {
					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT)
					{
						App->ui->score_koyori += 200;
					}
					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2)
					{
						App->ui->score_sho += 200;
					}
					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)
					{
						App->ui->score_junis += 200;
					}
					delete enemies[i];
					enemies[i] = nullptr;
					ninja_life = 0;
				}
			}

			//Enemy Drop Power Up
			if (c1->type == COLLIDER_TYPE::COLLIDER_REDOVNI && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2 || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)) {
				App->audio->PlaySoundEffects(fx_death);
				App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
				AddEnemy(ENEMY_TYPES::POWERUP, enemies[i]->position.x, enemies[i]->position.y);
				if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT) 
				{
					App->ui->score_koyori += 200;
				}
				if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2)
				{
					App->ui->score_sho += 200;
				}
				if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)
				{
					App->ui->score_junis += 200;
				}
				delete enemies[i];
				enemies[i] = nullptr;
			}

			if (c1->type == COLLIDER_TYPE::COLLIDER_ELF && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2 || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)) {
				if (life_elf>50 || enemies[i]->position.x >4550) {
					App->enemies->AddEnemy(ENEMY_TYPES::ULTI, enemies[i]->position.x, enemies[i]->position.y);
					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					delete enemies[i];
					enemies[i] = nullptr;
				}
				LOG("%i", life_elf);
				life_elf++;
			}
			if (c1->type == COLLIDER_TYPE::COLLIDER_TURRET && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2 || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)) {
				if (turret_life>50|| enemies[i]->position.x >4550) {
					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					delete enemies[i];
					enemies[i] = nullptr;
				}
				turret_life++;
			}
			if (c1->type == COLLIDER_TYPE::COLLIDER_SHIPHEAD && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI2 || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_3_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_ULTI3)) {
				if (shiphead_life>50 || enemies[i]->position.x >4550) {
					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					delete enemies[i];
					enemies[i] = nullptr;
				}
				shiphead_life++;
			}
		
			if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER  && c1->type == COLLIDER_TYPE::COLLIDER_ENTITY) {
				
				if (c2 == App->player2->coll) {
					App->audio->PlaySoundEffects(catch_bomb);
					App->ui->num_ulti_sho++;
				}
				if (c2 == App->player3->coll) {
					App->audio->PlaySoundEffects(catch_bomb);
					App->ui->num_life_junis++;
				}
				delete enemies[i];
				enemies[i] = nullptr;
			}
			break;
		}
		
		

	}

}
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleSceneForest.h"
#include "Enemy.h"
#include "Enemy_GreenOvni.h"
#include "Enemy_RedOvni.h"
#include "Enemy_Ninja.h"
#include "Entity_PowerUp.h"
#include "Enemy_Coin.h"
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

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
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
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
			case ENEMY_TYPES::GREENOVNI:
				enemies[i] = new Enemy_GreenOvni(info.x, info.y);
				break;

			case ENEMY_TYPES::REDOVNI:
				enemies[i] = new Enemy_RedOvni(info.x, info.y);
				break;
			case ENEMY_TYPES::NINJA:
				enemies[i] = new Enemy_Ninja(info.x, info.y);
				break;
			case ENEMY_TYPES::POWERUP:
				enemies[i] = new EntityPowerUp(info.x, info.y);
				break;
			case ENEMY_TYPES::COIN:
				enemies[i] = new Enemy_Coin(info.x, info.y);
				break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	float speed = App->scene_forest->speed / SCREEN_SIZE;

	if (c2->type == COLLIDER_TYPE::COLLIDER_HITBOX&&c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHOT)
	{
		App->ui->num_life_koyori--;
	}
	
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{

			//Player collides w enemies
			if ((c2->type == COLLIDER_TYPE::COLLIDER_HITBOX || c2->type == COLLIDER_TYPE::COLLIDER_HITBOX_2) && c1->type == COLLIDER_TYPE::COLLIDER_ENEMY) {
				if (c2 == App->player->hitbox) {
					if (timer) {
						time_on_entry = SDL_GetTicks();
						timer = false;
					}
					current_time = SDL_GetTicks() - time_on_entry;
					if (current_time > 600) {
						if (App->player->power_up > 0) {
							App->particles->power_down.speed.x = speed;
							App->particles->power_down.speed.y = -2;
							App->particles->AddParticle(App->particles->power_down, App->player->position.x, App->player->position.y);
						}
						App->player->power_up--;
						timer = true;
					}
					App->audio->PlaySoundEffects(App->player->k_power_down);
					App->player->spin_pos = true;
					App->player->state = SPIN;
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
			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT) {
				
				num_ovni++;

					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					
					

				if (num_ovni >=4) {
					AddEnemy(ENEMY_TYPES::COIN, enemies[i]->position.x, enemies[i]->position.y);
					ninja_life = 0;
					num_ovni = 0;
				}
				delete enemies[i];
				enemies[i] = nullptr;
				App->ui->score_koyori += 200;
			
			}
			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT) {

				num_ovni++;
				if (num_ovni <4) {
					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					delete enemies[i];
					enemies[i] = nullptr;
				}
				if (num_ovni >= 4) {
					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					AddEnemy(ENEMY_TYPES::COIN, enemies[i]->position.x, enemies[i]->position.y);
					delete enemies[i];
					enemies[i] = nullptr;
					ninja_life = 0;
					num_ovni = 0;
				}
				App->ui->score_sho += 200;
				delete enemies[i];
				enemies[i] = nullptr;
			}
			

			//Coin
			if ((c2->type == COLLIDER_TYPE::COLLIDER_HITBOX || c2->type == COLLIDER_TYPE::COLLIDER_HITBOX_2) && c1->type == COLLIDER_TYPE::COLLIDER_COIN) {
				srand(time(NULL));

				if (c2 == App->player->hitbox) {

					typeofcoin = rand() % 5 + 1;
					switch (typeofcoin) {
					case 0:
						App->particles->coin_100.speed.x = speed;
						App->particles->coin_100.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_100, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_koyori += 100;
						delete enemies[i];
						enemies[i] = nullptr;
						break;
					case 1:
						App->particles->coin_200.speed.x = speed;
						App->particles->coin_200.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_200, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_koyori += 200;

						break;
						delete enemies[i];
						enemies[i] = nullptr;

					case 2:
						App->particles->coin_500.speed.x = speed;
						App->particles->coin_500.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_500, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_koyori += 500;

						break;
						delete enemies[i];
						enemies[i] = nullptr;
					case 3:
						App->particles->coin_1000.speed.x = speed;
						App->particles->coin_1000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_1000, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_koyori += 1000;

						delete enemies[i];
						enemies[i] = nullptr;
						break;
					case 4:
						App->particles->coin_2000.speed.x = speed;
						App->particles->coin_2000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_2000, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_koyori += 2000;
						delete enemies[i];
						enemies[i] = nullptr;
						break;
					case 5:
						App->particles->coin_4000.speed.x = speed;
						App->particles->coin_4000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_4000, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_koyori += 4000;

						delete enemies[i];
						enemies[i] = nullptr;

					}
				}
				if (c2 == App->player2->hitbox) {

					typeofcoin = rand() % 5 + 1;
					switch (typeofcoin) {
					case 0:
						App->particles->coin_100.speed.x = speed;
						App->particles->coin_100.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_100, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);

						App->ui->score_sho += 100;
						delete enemies[i];
						enemies[i] = nullptr;
						break;
					case 1:
						App->particles->coin_200.speed.x = speed;
						App->particles->coin_200.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_200, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);

						App->ui->score_sho += 200;
						break;
						delete enemies[i];
						enemies[i] = nullptr;

					case 2:
						App->particles->coin_500.speed.x = speed;
						App->particles->coin_500.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_500, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);

						App->ui->score_sho += 500;
						break;
						delete enemies[i];
						enemies[i] = nullptr;
					case 3:
						App->particles->coin_1000.speed.x = speed;
						App->particles->coin_1000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_1000, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);

						App->ui->score_sho += 1000;
						delete enemies[i];
						enemies[i] = nullptr;
						break;
					case 4:
						App->particles->coin_2000.speed.x = speed;
						App->particles->coin_2000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_2000, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);

						App->ui->score_sho += 2000;
						delete enemies[i];
						enemies[i] = nullptr;
						break;
					case 5:
						App->particles->coin_4000.speed.x = speed;
						App->particles->coin_4000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_4000, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);

						App->ui->score_sho += 4000;
						delete enemies[i];
						enemies[i] = nullptr;

					}
				}

			}

			//Power Ups
			if ((c2->type == COLLIDER_TYPE::COLLIDER_PLAYER ) && c1->type == COLLIDER_TYPE::COLLIDER_POWER_UP) {
				if (c2 == App->player->coll) {
					if (App->player->power_up < 2) {
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
					delete enemies[i];
					enemies[i] = nullptr;
				}
				if (c2 == App->player2->coll) {
					if (App->player2->power_up < 2) {
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
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			if ((c2->type == COLLIDER_TYPE::COLLIDER_HITBOX || c2->type == COLLIDER_TYPE::COLLIDER_HITBOX_2) && c1->type == COLLIDER_TYPE::COLLIDER_COIN) {
				if (c2 == App->player->hitbox) {
					App->player->coin++;
					delete enemies[i];
					enemies[i] = nullptr;
				}
				if (c2 == App->player2->hitbox) {
					App->player2->coin++;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}

			//Shooting trigger


			//Kill ninja
			if (c1->type == COLLIDER_TYPE::COLLIDER_NINJA && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT) {
				ninja_life++;
				if (ninja_life == 1) {
					App->particles->AddParticle(App->particles->spark, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->spark.speed.x = speed;
				}
				if (ninja_life == 2) {
					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					App->ui->score_koyori += 200;
					delete enemies[i];
					enemies[i] = nullptr;
					ninja_life = 0;
				}
			}
			if (c1->type == COLLIDER_TYPE::COLLIDER_NINJA && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT) {
				ninja_life++;
				if (ninja_life == 1) {
					App->particles->AddParticle(App->particles->spark, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->spark.speed.x = speed;
				}
				if (ninja_life == 2) {
					App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					App->ui->score_sho += 200;
					delete enemies[i];
					enemies[i] = nullptr;
					ninja_life = 0;
				}
			}
			//Enemy Drop Power Up
			if (c1->type == COLLIDER_TYPE::COLLIDER_REDOVNI && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT) {
				App->audio->PlaySoundEffects(fx_death);
				App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
				AddEnemy(ENEMY_TYPES::POWERUP, enemies[i]->position.x, enemies[i]->position.y);
				App->ui->score_koyori += 200;
				delete enemies[i];
				enemies[i] = nullptr;
			}
			if (c1->type == COLLIDER_TYPE::COLLIDER_REDOVNI && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_2_SHOT) {
				App->audio->PlaySoundEffects(fx_death);
				App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
				AddEnemy(ENEMY_TYPES::POWERUP, enemies[i]->position.x, enemies[i]->position.y);
				App->ui->score_sho += 200;
				delete enemies[i];
				enemies[i] = nullptr;
			}
			
			break;
		}
		
		

	}

}
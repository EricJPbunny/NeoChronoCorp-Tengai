#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Enemy_GreenOvni.h"
#include "Enemy_RedOvni.h"
#include "Enemy_Ninja.h"
#include "ModuleParticles.h"
#include "Enemy_ShipHead.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
	GREENOVNI,
	REDOVNI,
	NINJA,
	ARCHER,
	BIRD,
	KNIFE,
	POWERUP,
	COIN,
	BOSSHEAD,
	TURRET,
	PALACE,
	BUDA,
	ELF,
	HEMISPHERE,
	ULTI,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y, path_type;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, int path_type = 0);

private:

	void SpawnEnemy(const EnemyInfo& info);

public:
	float speed = 0.2f;
	Mix_Chunk* fx_death = nullptr;
private:

	bool timer = false;
	int current_time = 700, time_on_entry = 0;

	bool timer_2 = false;
	int current_time_2 = 700, time_on_entry_2 = 0;
	int bulletsize=0;

	Mix_Chunk* s_power_down = nullptr;
	Mix_Chunk* j_power_down = nullptr;
	Mix_Chunk* catch_bomb = nullptr;
	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
	SDL_Texture* puSprites;
	Particle coin_type;
	fPoint pos;
	PARTICLE_TYPE particle_type = PARTICLE_NONE;

	int ninja_life = 0,shiphead_life=0,turret_life=0,palace_life=0;
	int num_ovni = 0;
	int life_elf = 0;
	int typeofcoin;
};

#endif // __ModuleEnemies_H__
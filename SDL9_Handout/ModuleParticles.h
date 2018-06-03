#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

struct Mix_Chunk;

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum PARTICLE_TYPE
{
	PARTICLE_NONE,
	PARTICLE_SHOT,
	PARTICLE_SHOT_2,
	PARTICLE_SHOT_3,
	PARTICLE_COIN,
	PLAYER_ENEMY,
	PLAYER_REDOVNI,
	PLAYER_NINJA,
	PARTICLE_POWER_UP_KOYORI,
	PARTICLE_POWER_UP_SHO,
	PARTICLE_POWER_UP_JUNIS,
	PARTICLE_POWER_DOWN,
	PARTICLE_SHURIKEN,

};

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, PARTICLE_TYPE particle_type = PARTICLE_NONE, Uint32 delay = 0 );

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:

	Mix_Chunk* shoot_audio = nullptr;
	Mix_Chunk* shoot_sho = nullptr;
	Mix_Chunk* power_up_koyori_fx = nullptr;
	Mix_Chunk* power_up_sho_fx = nullptr;
	Mix_Chunk* power_up_junis_fx = nullptr;
	Mix_Chunk* koyori_death = nullptr;
	Mix_Chunk* sho_death = nullptr;
	Mix_Chunk* coin_fx = nullptr;
	Mix_Chunk* shoot_junis = nullptr;
	Mix_Chunk* junis_death = nullptr;
	Particle bullet, bullet2, bullet3, bullet4, bullet5, explosion, spark;
	Particle shoot, shoot1, shoot2;
	Particle shoot_sho_big, shoot_sho_big_1, shoot_sho_big_2;
	Particle mirror_shoot;
	Particle c_mirror_green, c_mirror_blue, c_mirror_cyan;
	Particle cat_shoot, egg_shoot, basaro_shot;
	Particle power_up, power_down;
	Particle coin_100, coin_200, coin_500, coin_1000, coin_2000, coin_4000;
	Particle shuriken;
	Particle kunai, kunai1, kunai2;
	Particle shuriken_socrates_1, shuriken_socrates_2, shuriken_socrates_3, shuriken_socrates_4, shuriken_socrates_5, shuriken_socrates_6, shuriken_socrates_7, shuriken_socrates_8;
	Particle fire, fire2, fire3, fire4, fire5, fire6, fire7, fire8, fire9, fire10;
	Particle enemie_shoot, archer_shoot, bird_shoot, bird_shoot2;
	Particle shipHead_shoot;
	Particle elf_shuriken, elf_shuriken2, elf_shuriken3, elf_shuriken4, elf_shuriken5, elf_shuriken6, elf_shuriken7, elf_shuriken8, elf_shuriken9, elf_shuriken10, elf_shuriken11, elf_shuriken12, elf_shuriken13, elf_shuriken14, elf_shuriken15, elf_shuriken16, elf_shuriken_shiny;
	Particle elf_shoot, elf_shoot2, elf_shoot3, elf_shoot4, elf_shoot5, elf_shoot6,elf_shoot7,elf_shoot8;
};

#endif // __MODULEPARTICLES_H__
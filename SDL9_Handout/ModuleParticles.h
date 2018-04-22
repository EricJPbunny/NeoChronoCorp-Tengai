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
	PLAYER_ENEMY,
	PARTICLE_POWER_UP_KOYORI,
	PARTICLE_POWER_UP_SHO,
	PARTICLE_POWER_DOWN,

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
	Particle bullet, bullet2, bullet3, bullet4, bullet5, explosion, spark;
	Particle shoot, shoot1, shoot2;
	Particle mirror_shoot;
	Particle c_mirror_green, c_mirror_blue, c_mirror_cyan;
	Particle cat_shoot, egg_shoot, basaro_shot;
	Particle power_up, power_down;
};

#endif // __MODULEPARTICLES_H__
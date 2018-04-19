#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	//Koyori Bullets
	bullet.anim.PushBack({ 24, 136, 13, 13 });
	bullet.anim.loop = true;
	bullet.life = 1400;
	bullet.speed.x = 12;

	bullet2.anim.PushBack({ 48, 136, 13, 13 });
	bullet2.anim.loop = true;
	bullet2.life = 1400;
	bullet2.speed.x = 12;

	bullet3.anim.PushBack({ 72, 136, 13, 13 });
	bullet3.anim.loop = true;
	bullet3.life = 1400;
	bullet3.speed.x = 12;

	bullet4.anim.PushBack({ 97, 136, 13, 13 });
	bullet4.anim.loop = true;
	bullet4.life = 1400;
	bullet4.speed.x = 12;

	bullet5.anim.PushBack({ 120, 136, 13, 13 });
	bullet5.anim.loop = true;
	bullet5.life = 1400;
	bullet5.speed.x = 12;

	//Enemies Explosion

	explosion.anim.PushBack({ 46, 44, 24, 212 });
	explosion.anim.loop = true;
	explosion.life = 1400;
	
	explosion2.anim.PushBack({ 48, 54, 81, 207 });
	explosion2.anim.loop = true;
	explosion2.life = 1400;
	
	explosion3.anim.PushBack({ 54, 61, 140, 206 });
	explosion3.anim.loop = true;
	explosion3.life = 1400;
	
	explosion4.anim.PushBack({ 50, 57, 202, 209 });
	explosion4.anim.loop = true;
	explosion4.life = 1400;
	
	explosion5.anim.PushBack({ 53, 60, 264, 207 });
	explosion5.anim.loop = true;
	explosion5.life = 1400;
	
	explosion6.anim.PushBack({ 52, 63, 326, 207 });
	explosion6.anim.loop = true;
	explosion6.life = 1400;

	explosion7.anim.PushBack({ 53, 64, 387, 207 });
	explosion7.anim.loop = true;
	explosion7.life = 1400;

	explosion8.anim.PushBack({ 53, 64, 387, 207 });
	explosion8.anim.loop = true;
	explosion8.life = 1400;

	explosion9.anim.PushBack({ 56, 63, 23, 283 });
	explosion9.anim.loop = true;
	explosion9.life = 1400;

	explosion10.anim.PushBack({ 56, 64, 90, 283 });
	explosion10.anim.loop = true;
	explosion10.life = 1400;

	explosion11.anim.PushBack({ 53, 60, 157, 282 });
	explosion11.anim.loop = true;
	explosion11.life = 1400;

	explosion12.anim.PushBack({ 51, 59, 223, 282 });
	explosion12.anim.loop = true;
	explosion12.life = 1400;


}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/sprite/particles.png");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	// Unload fx

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				//App->audio->PlayFx(p->fx);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if(collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1)
		{
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}


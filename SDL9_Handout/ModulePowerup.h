#ifndef __MODULEPOWERUPS_H__
#define __MODULEPOWERUPS_H__

#include "Module.h"
#include "Enemy_RedOvni.h"

#define MAX_POWERUP 20
#define MAX_ULTI 20


enum pu_type
{

	power,
	ult
};

struct Powerup
{
	bool enabled = false;
	Animation anim;
	iPoint position;
	pu_type type;
	Collider* collider = nullptr;
	void draw(SDL_Texture*);

};

struct Ulti
{
	bool enabled = false;
	Animation anim;
	iPoint position;
	pu_type type;
	Collider* collider = nullptr;
	void draw(SDL_Texture*);

};

class ModulePowerup : public Module
{
public:
	ModulePowerup();
	~ModulePowerup();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	


private:
	SDL_Texture * graphics = nullptr;
	Powerup* powerUp[MAX_POWERUP];
	Ulti* powerUlti[MAX_ULTI];


public:
	Powerup powercharge;
	Ulti ultcharge;

};

#endif
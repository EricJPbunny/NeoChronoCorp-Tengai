#ifndef __MODULECOIN_H__
#define __MODULECOIN_H__

#include "Module.h"
#include "Enemy_GreenOvni.h"

#define MAX_COIN 20


enum pu_type
{
	coin,
	ult
};

struct Coin
{
	bool enabled = false;
	Animation anim;
	iPoint position;
	pu_type type;
	Collider* collider = nullptr;
	void draw(SDL_Texture*);

};

class ModuleCoin : public Module
{
public:
	ModuleCoin();
	~ModuleCoin();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();



private:
	SDL_Texture * graphics = nullptr;
	Coin* coin[MAX_COIN];

public:
	Coin coincharge;
	Coin ultcharge;

};

#endif

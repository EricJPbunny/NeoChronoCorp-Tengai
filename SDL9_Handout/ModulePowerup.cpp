#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "Enemy.h"
#include "Enemy_RedOvni.h"
#include "ModulePowerup.h"


ModulePowerup::ModulePowerup()
{
	for (uint i = 0; i < MAX_POWERUP; ++i)
		powerUp[i] = nullptr;

	for (uint i = 0; i < MAX_ULTI; ++i)
		powerUlti[i] = nullptr;
}

ModulePowerup::~ModulePowerup() 
{

};

bool ModulePowerup::Init() 
{
	return true;
}


bool ModulePowerup::CleanUp()
{
	return true;
};

bool ModulePowerup::Start() 
{
	graphics = App->textures->Load("assets/sprite/PowerUp.png");
	return true;
};

update_status ModulePowerup::Update() 
{
	for (uint i = 0; i < MAX_POWERUP; ++i)
		if (powerUp[i] != nullptr)
		{
			powerUp[i]->draw(graphics);
		}

	for (uint i = 0; i < MAX_ULTI; ++i)
		if (powerUlti[i] != nullptr)
		{
			powerUlti[i]->draw(graphics);
		}
	return UPDATE_CONTINUE;
};

void Powerup::draw(SDL_Texture* text) 
{
	Animation* current_animation = &anim;
	App->render->Blit(text, position.x, position.y, &(current_animation->GetCurrentFrame()));
}

void Ulti::draw(SDL_Texture* text)
{
	Animation* current_animation = &anim;
	App->render->Blit(text, position.x, position.y, &(current_animation->GetCurrentFrame()));
}
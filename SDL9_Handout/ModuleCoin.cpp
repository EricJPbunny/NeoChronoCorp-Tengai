#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "Enemy.h"
#include "Enemy_GreenOvni.h"
#include "ModuleCoin.h"


ModuleCoin::ModuleCoin()
{
	for (uint i = 0; i < MAX_COIN; ++i)
		coin[i] = nullptr;
}

ModuleCoin::~ModuleCoin()
{

};

bool ModuleCoin::Init()
{
	return true;
}


bool ModuleCoin::CleanUp()
{
	return true;
};

bool ModuleCoin::Start()
{
	graphics = App->textures->Load("assets/sprite/Coin.png");
	return true;
};

update_status ModuleCoin::Update()
{
	for (uint i = 0; i < MAX_COIN; ++i)
		if (coin[i] != nullptr)
		{
			coin[i]->draw(graphics);
		}
	return UPDATE_CONTINUE;
};

void Coin::draw(SDL_Texture* text)
{
	Animation* current_animation = &anim;
	App->render->Blit(text, position.x, position.y, &(current_animation->GetCurrentFrame()));
}
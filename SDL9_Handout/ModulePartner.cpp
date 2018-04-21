#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneForest.h"
#include "ModulePlayer.h"
#include "ModulePartner.h"
#include "ModuleUI.h"


ModulePartner::ModulePartner()
{
	graphics = nullptr;
	current_animation = nullptr;

	spawn.PushBack({22,209,3,5});
	spawn.PushBack({ 57,208,12,7 });
	spawn.PushBack({ 95,206,18,11 });
	spawn.PushBack({ 132,211,21,12 });
	spawn.speed = 0.15f;

	iddle.PushBack({ 170,204,25,15 });
	iddle.PushBack({ 210,205,25,14 });
	iddle.PushBack({ 250,205,25,15 });
	iddle.PushBack({ 291,205,25,14 });
	iddle.speed = 0.15f;

	charging.PushBack({ 12,242,26,18 });
	charging.PushBack({ 52,239,28,22 });
	charging.PushBack({ 90,238,31,24 });
	charging.PushBack({ 130,238,31,24 });
	charging.PushBack({ 170,238,31,25 });
	charging.PushBack({ 211,238,30,24 });
	charging.PushBack({ 250,239,31,22 });
	charging.PushBack({ 291,237,29,23 });
	charging.PushBack({ 331,239,27,19 });
	charging.PushBack({ 373,240,26,18 });
	charging.speed = 0.10f;
	
}

ModulePartner::~ModulePartner() 
{
	//destroyer
}

bool ModulePartner::Start() 
{
	LOG("Loading partner textures");
	graphics = App->textures->Load("assets/sprite/miko.png");
	if (graphics == nullptr) 
	{
		LOG("Could not load partner textures")
			return false;
	}
	position.x = App->player->position.x - 20;
	position.y = App->player->position.y + 20;
	return true;
}

bool ModulePartner::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(graphics);
	graphics = nullptr;
	if (graphics != nullptr) 
	{
		LOG("Could not unload partner textures")
			return false;
	}

	return true;
}

update_status ModulePartner::Update()
{
	switch (state) 
	{
	case NOT_EXISTING:
		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN) 
		{
			LOG("Partner spawned")
			state = LEVEL_ONE;
			current_animation = &iddle;
		}
		break;
	case LEVEL_TWO:

		position.x = App->player->position.x - 20;
		position.y = App->player->position.y - 25;
		current_animation = &iddle2;

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			LOG("Particle is spawned")
				// SHOOTING  _______________________________
		}
		break;
	case LEVEL_ONE:
		position.x = App->player->position.x - 20;
		position.y = App->player->position.y - 25;

		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
		{
			LOG("Partner Level UP")
				state = LEVEL_TWO;
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			LOG("Particle (2n level) is spawned");
				// SHOOTING  _______________________________
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)
		{
			LOG("Particle charge (2n level) is spawned");
				// SHOOTING  _______________________________
			current_animation = &charging;
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP)
		{
			LOG("Particle charge canceled (2n level) is spawned");
			// SHOOTING  _______________________________
			current_animation = &iddle;
		}
		break;
	}
	if (current_animation != nullptr) 
	{
		if (current_animation->Finished()) {
			current_animation->Reset();
			current_animation = &iddle;
		}
		SDL_Rect r = current_animation->GetCurrentFrame();

		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}

	return UPDATE_CONTINUE;
}
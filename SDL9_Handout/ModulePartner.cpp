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

#include "SDL\include\SDL_timer.h"

ModulePartner::ModulePartner()
{
	graphics = nullptr;
	current_animation = nullptr;

	spawn.PushBack({ 22,209,3,5 });
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
	aux = 0;
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
	CheckState();

	PerformActions();

	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) {
		App->player->power_up++;
	}
	if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN) {
		App->player->power_up--;
	}

	//Draw partner
	SDL_Rect r = current_animation->GetCurrentFrame();

	//Set position
	position.x = App->player->position.x - 20;
	position.y = App->player->position.y - 20;

	if (exist) {
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			if (shot_delay)
			{
				shot_entry = SDL_GetTicks();
				shot_delay = false;
			}
			shot_current = SDL_GetTicks() - shot_entry;
			if (shot_current > 300) {
				App->particles->AddParticle(App->particles->mirror_shoot, position.x + 10, position.y - 23, COLLIDER_PLAYER_2_SHOT);
				shot_delay = true;
			}
		}
		App->render->Blit(graphics, position.x + 10, position.y - 10 - r.h, &r);
	}
	return UPDATE_CONTINUE;
}



void ModulePartner::CheckState() {
	switch (state)
	{
	case NOT_EXISTING:
		time_shoot = true;
		if (App->player->power_up == 1) {
			state = SPAWN;
		}
		break;

	case SPAWN:
		if (spawn.Finished()) {
			spawn.Reset();
			state = LEVEL_ONE;
		}
		break;

	case LEVEL_ONE:
		if (App->player->power_up == 0) {
			state = NOT_EXISTING;
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 300) {
				time_shoot = true;
				state = LEVEL_ONE_CHARGE;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP) {
			time_shoot = true;
		}

		break;

	case LEVEL_ONE_CHARGE:
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP) {
			spawn.Reset();
			state = SHOT;
		}
		break;

	case SHOT:
		if (App->player->power_up == 0) {
			state = NOT_EXISTING;
		}
		if (time_cat) {
			time_on_entry = SDL_GetTicks();
			time_cat = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 4000) {
			state = LEVEL_ONE;
		}
		break;

	}
}



void ModulePartner::PerformActions()
{
	switch (state) {
	case NOT_EXISTING:
		current_animation = &iddle;
		exist = false;
		break;

	case SPAWN:
		current_animation = &spawn;
		exist = true;
		if (spawn.Finished()) {
			spawn.Reset();
		}
		break;

	case LEVEL_ONE:
		current_animation = &iddle;
		exist = true;
		break;

	case LEVEL_ONE_CHARGE:
		if (current_animation != &charging && spawn.Finished()) {
			current_animation = &charging;
		}
		if (charging.Finished()) {
			charging.Reset();
		}
		break;
	case SHOT:
		current_animation = &iddle;
		if (shot_delay)
		{
			shot_entry = SDL_GetTicks();
			shot_delay = false;
		}
		shot_current = SDL_GetTicks() - shot_entry;
		if (shot_current > 200) {
			switch (num_bullet) {
			case 1:
				App->particles->AddParticle(App->particles->c_mirror_green, position.x + 10, position.y - 23, COLLIDER_PLAYER_2_SHOT);
				break;
			case 2:
				App->particles->AddParticle(App->particles->c_mirror_blue, position.x + 10, position.y - 23, COLLIDER_PLAYER_2_SHOT);
				break;
			case 3:
				App->particles->AddParticle(App->particles->c_mirror_cyan, position.x + 10, position.y - 23, COLLIDER_PLAYER_2_SHOT);
				num_bullet = 0;
				break;
			}
			num_bullet++;
			shot_delay = true;
		}
		break;
	}
}
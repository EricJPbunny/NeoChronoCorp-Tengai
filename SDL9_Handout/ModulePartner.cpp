#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneAir.h"
#include "ModulePlayer.h"
#include "ModulePartner.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"

#include "SDL\include\SDL_timer.h"

ModulePartner::ModulePartner()
{
	graphics = nullptr;
	current_animation = nullptr;

	spawn.PushBack({ 22,209,3,5 });
	spawn.PushBack({ 57,208,12,6 });
	spawn.PushBack({ 95,206,18,11 });
	spawn.PushBack({ 132,206,21,12 });
	spawn.speed = 0.15f;

	iddle.PushBack({ 170,204,25,15 });
	iddle.PushBack({ 210,204,25,15 });
	iddle.PushBack({ 250,204,25,15 });
	iddle.PushBack({ 290,204,25,15 });
	iddle.speed = 0.15f;

	charging.PushBack({ 12,242,26,18 });
	charging.PushBack({ 52,239,28,22 });
	charging.PushBack({ 90,238,31,24 });
	charging.speed = 0.20f;

	decharging.PushBack({ 250,239,31,22 });
	decharging.PushBack({ 291,237,29,23 });
	decharging.PushBack({ 331,239,27,19 });
	decharging.PushBack({ 373,240,26,18 });
	decharging.speed = 0.25f;

	charged.PushBack({ 130,238,31,24 });
	charged.PushBack({ 170,238,31,24 });
	charged.PushBack({ 210,238,31,24 });
	charged.PushBack({ 170,238,31,24 });
	charged.speed = 0.15f;

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
	exist = false;
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
		App->render->Blit(graphics, position.x + 10, position.y - 10 - r.h, &r);
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			if (shot_delay)
			{
				shot_entry = SDL_GetTicks();
				shot_delay = false;
			}
			shot_current = SDL_GetTicks() - shot_entry;
			if (shot_current > 300) {
				if (App->player->power_up == 2) {
					App->particles->AddParticle(App->particles->basaro_shot, position.x + 10, position.y - 13, COLLIDER_PLAYER_2_SHOT);
					App->particles->basaro_shot.fx_played = 1;
				}
				App->particles->AddParticle(App->particles->basaro_shot, position.x + 10, position.y - 23, COLLIDER_PLAYER_2_SHOT);
				shot_delay = true;
			}
		}
	}
	
	return UPDATE_CONTINUE;
}



void ModulePartner::CheckState() {
	switch (state)
	{
	case NOT_EXISTING:
		if (App->player->power_up == 1) {
			exist = true;
			state = SPAWN;
		}
		break;

	case SPAWN:
		if (spawn.Finished()) {
			spawn.Reset();
			state = LEVEL_ONE;
		}
	case LEVEL_ONE:
		if (App->player->power_up == 0) {
			exist = false;
			state = NOT_EXISTING;
		}
		if (App->player->power_up == 2) {
			state = LEVEL_FOUR;
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 800) {
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
			state = EGG_SHOT;
		}
		break;

	case EGG_SHOT:
		if (decharging.Finished()) {
			decharging.Reset();
			create_bullet = true;
			state = LEVEL_ONE;
		}
		break;
		
	case LEVEL_FOUR:
		if (App->player->power_up <= 1) {
			state = LEVEL_ONE;
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 800) {
				time_shoot = true;
				state = LEVEL_FOUR_CHARGE;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP) {
			time_shoot = true;
		}
		break;

	case LEVEL_FOUR_CHARGE:
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP) {
			state = CAT_SHOT;
		}
		break;

	case CAT_SHOT:
		if (decharging.Finished()) {
			decharging.Reset();
			create_bullet = true;
			state = LEVEL_FOUR;
		}
		break;
	}
}



void ModulePartner::PerformActions()
{
	switch (state) {
	case NOT_EXISTING:
		current_animation = &iddle;
		break;

	case SPAWN:
		current_animation = &spawn;
		break;

	case LEVEL_ONE:
		current_animation = &iddle;
		if (charging.Finished()) {
			charging.Reset();
		}
		break;

	case LEVEL_ONE_CHARGE:
		if (!charging.Finished()) {
			current_animation = &charging;
		}
		else {
			current_animation = &charged;
		}
		break;

	case EGG_SHOT:
		current_animation = &decharging;
		if (create_bullet) {
			App->particles->AddParticle(App->particles->egg_shoot, position.x, position.y-24, COLLIDER_PLAYER_SHOT);
			create_bullet = false;
		}
		break;

	case LEVEL_FOUR:
		current_animation = &iddle;
		if (charging.Finished()) {
			charging.Reset();
		}
		break;

	case LEVEL_FOUR_CHARGE:
		if (!charging.Finished()) {
			current_animation = &charging;
		}
		else {
			current_animation = &charged;
		}
		break;

	case CAT_SHOT:
		current_animation = &decharging;
		if (create_bullet) {
			App->particles->AddParticle(App->particles->cat_shoot, position.x, position.y - 26, COLLIDER_PLAYER_SHOT);
			App->particles->cat_shoot.speed.x = App->enemies->speed+3;
			create_bullet = false;
		}
		break;
	}
}
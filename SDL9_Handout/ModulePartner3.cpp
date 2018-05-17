#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneAir.h"
#include "ModulePlayer3.h"
#include "ModulePartner3.h"
#include "ModuleUI.h"


#include "SDL\include\SDL_timer.h"

ModulePartner3::ModulePartner3()
{
	graphics = nullptr;
	current_animation = nullptr;

	spawn.PushBack({ 14,212,5,3 });
	spawn.PushBack({ 45,210,12,6 });
	spawn.PushBack({ 80,210,19,8 });
	spawn.PushBack({ 126,209,23,10 });
	spawn.speed = 0.15f;


	spawn_reverse.PushBack({ 126,209,23,10 });
	spawn_reverse.PushBack({ 80,210,19,8 });
	spawn_reverse.PushBack({ 45,210,12,6 });
	spawn_reverse.PushBack({ 14,212,5,3 });
	spawn_reverse.speed = 0.30f;


	iddle.PushBack({ 411,206,31,13 });
	iddle.PushBack({ 372,203,30,14 });
	iddle.PushBack({ 455,205,30,13 });
	iddle.PushBack({ 337,203,27,14 });
	iddle.speed = 0.15f;

	
	charging.PushBack({ 282,199,28,21 });
	charging.PushBack({ 247,198,24,21 });
	charging.PushBack({ 208,197,27,21 });
	charging.PushBack({ 168,200,27,21 });
	charging.speed = 0.10f;


	pre_shot.PushBack({ 9,4,48,42 });
	pre_shot.PushBack({ 74,4,53,46 });
	pre_shot.PushBack({ 147,5,58,52 });
	pre_shot.PushBack({ 222,7,58,53 });
	pre_shot.PushBack({ 289,6,64,57 });
	pre_shot.PushBack({ 377,8,64,58 });
	pre_shot.speed = 0.15f;


	shot.PushBack({ 10,72,76,37 });
	shot.PushBack({ 94,74,76,38 });
	shot.PushBack({ 192,76,79,38 });
	shot.PushBack({ 287,82,79,37 });
	shot.PushBack({ 389,79,79,38 });
	shot.PushBack({ 13,135,79,37 });
	shot.PushBack({ 107,136,76,37 });
	shot.PushBack({ 198,137,76,38 });
	shot.speed = 0.15f;


}

ModulePartner3::~ModulePartner3()
{
	//destroyer
}

bool ModulePartner3::Start()
{
	LOG("Loading partner textures");
	graphics = App->textures->Load("assets/sprite/Socrates_Spritesheet.png");
	if (graphics == nullptr)
	{
		LOG("Could not load partner textures")
			return false;
	}

	position.x = App->player3->position.x;
	position.y = App->player3->position.y;
	return true;
}

bool ModulePartner3::CleanUp()
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


update_status ModulePartner3::Update()
{
	CheckState();

	PerformActions();

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN) {
		App->player3->power_up++;
	}
	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN) {
		App->player3->power_up--;
	}

	//Draw partner
	SDL_Rect r = current_animation->GetCurrentFrame();

	if (exist) {
		App->render->Blit(graphics, position.x + 10, position.y - 13 - r.h, &r);
	}

	//Set Position
	if (movement) {
		position.x = App->player3->position.x - 25;
		position.y = App->player3->position.y - 10;
	}
	if (!movement && !charged_shoot) {
		position.x = App->player3->position.x + 25;
		position.y = App->player3->position.y - 20;
	}
	else if (charged_shoot) {
		position.x += App->scene_air->speed / SCREEN_SIZE;
	}

	return update_status::UPDATE_CONTINUE;
}


void ModulePartner3::CheckState()
{
	//Create bool controls
	bool pressed_space_3 = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_REPEAT;
	bool release_space_3 = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_UP;


	switch (state)
	{

	case NOT_EXISTING_3:
		movement = true;
		time_socrates = true;
		if (App->player3->power_up == 1) 
		{
			state = SPAWN_3;
		}
		break;

	case SPAWN_3:
		if (spawn.Finished()) {
			spawn.Reset();
			state = LEVEL_ONE_3;
		}
		break;

	case LEVEL_ONE_3:
		if (App->player3->power_up == 0) 
		{
			state = NOT_EXISTING_3;
		}
		if (App->player3->power_up == 2) 
		{
			state = LEVEL_TWO_3;
		}

		//make it charge
		if (pressed_space_3) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 300) {
				time_shoot = true;
				state = LEVEL_ONE_CHARGE_3;
			}
		}
		if (release_space_3) {
			time_shoot = true;
		}
		break;

	case LEVEL_ONE_CHARGE_3:
		//make it shot fire while pressing a key
		if (release_space_3) {
			spawn.Reset();
			spawn_reverse.Reset();
			charged_shoot = true;
			state = FIRE_3;
		}
		break;

	case LEVEL_TWO_3:
		if (App->player3->power_up <= 1)
		{
			state = LEVEL_ONE_3;
		}

		if (App->player3->power_up == 3)
		{
			state = LEVEL_THREE_3;
		}

		//make it charge
		if (pressed_space_3) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 300) {
				time_shoot = true;
				state = LEVEL_ONE_CHARGE_3;
			}
		}
		if (release_space_3) {
			time_shoot = true;
		}
		break;


	case LEVEL_THREE_3:
		if (App->player3->power_up <= 2)
		{
			state = LEVEL_TWO_3;
		}

		if (App->player3->power_up == 4)
		{
			state = LEVEL_FOUR_3;
		}

		//make it charge
		if (pressed_space_3) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 300) {
				time_shoot = true;
				state = LEVEL_ONE_CHARGE_3;
			}
		}
		if (release_space_3) {
			time_shoot = true;
		}
		break;


	case LEVEL_FOUR_3:
		if (App->player3->power_up <= 3)
		{
			state = LEVEL_THREE_3;
		}

		//make it charge
		if (pressed_space_3) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 300) {
				time_shoot = true;
				state = LEVEL_ONE_CHARGE_3;
			}
		}
		if (release_space_3) {
			time_shoot = true;
		}
		break;


	case FIRE_3:
		if (App->player3->power_up == 0) {
			state = NOT_EXISTING_3;
		}

		if (time_socrates) {
			time_on_entry = SDL_GetTicks();
			time_socrates = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 6500) {
			state = DESPAWN_3;
		}
		break;


	case DESPAWN_3:
		if (spawn_reverse.Finished()) {
			spawn_reverse.Reset();
			charged_shoot = false;
			movement = true;
			time_socrates = true;
			state = SPAWN_3;
		}
		break;
	}
}


void ModulePartner3::PerformActions()
{
	switch (state) {
	case NOT_EXISTING_3:
		current_animation = &iddle;
		exist = false;
		break;

	case SPAWN_3:
		current_animation = &spawn;
		exist = true;
		break;

	case LEVEL_ONE_3:
		current_animation = &iddle;
		exist = true;
		break;

	case LEVEL_ONE_CHARGE_3:
		if (!spawn_reverse.Finished()) {
			current_animation = &spawn_reverse;
		}
		if (spawn_reverse.Finished() && !spawn.Finished()) {
			movement = false;
			current_animation = &spawn;
		}
		if (spawn_reverse.Finished() && spawn.Finished()) {
			current_animation = &charging;
		}
		break;

	case LEVEL_TWO_3:
		current_animation = &iddle;
		exist = true;
		break;

	case LEVEL_THREE_3:
		current_animation = &iddle;
		exist = true;
		break;

	case LEVEL_FOUR_3:
		current_animation = &iddle;
		exist = true;
		break;

	case FIRE_3:
		current_animation = &pre_shot;
		if (pre_shot.Finished()) {
			current_animation = &shot;

		}
		break;

	case DESPAWN_3:
		current_animation = &spawn_reverse;
		break;


	}
}
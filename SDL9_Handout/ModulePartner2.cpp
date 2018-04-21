#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneForest.h"
#include "ModulePlayer2.h"
#include "ModulePartner2.h"
#include "ModuleUI.h"

#include "SDL\include\SDL_timer.h"


ModulePartner2::ModulePartner2()
{
	graphics = nullptr;
	current_animation = nullptr;

	spawn.PushBack({6,146,10,11});
	spawn.PushBack({ 19,146,10,11 });
	spawn.PushBack({ 31,146,10,11 });
	spawn.PushBack({ 51,147,10,11 });
	spawn.speed = 0.30f;

	spawn_reverse.PushBack({ 51,147,10,11 });
	spawn_reverse.PushBack({ 31,146,10,11 });
	spawn_reverse.PushBack({ 19,146,10,11 });
	spawn_reverse.PushBack({ 6,146,10,11 });
	spawn_reverse.speed = 0.30f;

	spawn2.PushBack({ 6,146,10,11 });
	spawn2.PushBack({ 19,146,10,11 });
	spawn2.PushBack({ 31,146,10,11 });
	spawn2.PushBack({ 51,147,10,11 });
	spawn2.speed = 0.30f;

	spawn_reverse2.PushBack({ 51,147,10,11 });
	spawn_reverse2.PushBack({ 31,146,10,11 });
	spawn_reverse2.PushBack({ 19,146,10,11 });
	spawn_reverse2.PushBack({ 6,146,10,11 });
	spawn_reverse2.speed = 0.30f;

	iddle.PushBack({ 123,175,15,13 });
	iddle.PushBack({ 148,175,15,13 });
	iddle.PushBack({ 171,175,15,13 });
	iddle.PushBack({ 193,175,15,13 });
	iddle.speed = 0.15f;

	iddle2.PushBack({ 123,175,15,13 });
	iddle2.PushBack({ 148,175,15,13 });
	iddle2.PushBack({ 171,175,15,13 });
	iddle2.PushBack({ 193,175,15,13 });
	iddle2.speed = 0.15f;

	charging.PushBack({ 5,175,25,13 });
	charging.PushBack({ 35,175,24,13 });
	charging.PushBack({ 64,175,23,13 });
	charging.PushBack({ 92,175,22,13 });
	charging.speed = 0.10f;

	charging2.PushBack({ 5,175,25,13 });
	charging2.PushBack({ 35,175,24,13 });
	charging2.PushBack({ 64,175,23,13 });
	charging2.PushBack({ 92,175,22,13 });
	charging2.speed = 0.10f;

	
}

ModulePartner2::~ModulePartner2() 
{
	//destroyer
}

bool ModulePartner2::Start() 
{
	LOG("Loading partner textures");
	graphics = App->textures->Load("assets/sprite/Sho_Spritesheet.png");
	if (graphics == nullptr) 
	{
		LOG("Could not load partner textures")
			return false;
	}
	position.x = App->player2->position.x;
	position.y = App->player2->position.y ;
	return true;
}

bool ModulePartner2::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(graphics);
	if (graphics != nullptr) 
	{
		LOG("Could not unload partner 2 textures")
			return false;
	}

	return true;
}

update_status ModulePartner2::Update()
{
	//check state
	CheckState();

	//state actions
	PerformActions();

	//Prove
	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN) {
		App->player2->power_up++;
	}
	if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN) {
		App->player2->power_up--;
	}

	//Set Position
	if (movement) {
		position.x = App->player2->position.x - 25;
		position.y = App->player2->position.y - 10;
	}
	if (!movement) {
		position.x = App->player2->position.x + 25;
		position.y = App->player2->position.y - 20;
	}

	//Draw Partner
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect r1 = current_animation_2->GetCurrentFrame();
	if (exist) {
		if (movement) {
			if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN) {
				App->particles->AddParticle(App->particles->mirror_shoot, position.x + 10, position.y - 23, COLLIDER_PLAYER_2_SHOT);
			}
		}
		App->render->Blit(graphics, position.x + 10, position.y - 10 - r.h, &r);
	}
	if (exist_2) {
		if (movement) {
			if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN) {
				App->particles->AddParticle(App->particles->mirror_shoot, position.x + 5, position.y - 8, COLLIDER_PLAYER_2_SHOT);
			}
		}
		App->render->Blit(graphics, position.x+5, position.y+5 - r1.h, &r1);
	}
	
	return UPDATE_CONTINUE;
}

void ModulePartner2::CheckState() 
{
	//Mirror 1
	switch (state) {
	case NOT_EXISTING_2:
		movement = true;
		time_mirror = true;
		if (App->player2->power_up == 1) {
			state = SPAWN;
		}
		break;

	case SPAWN:
		if (spawn.Finished()) {
			spawn.Reset();
			state = LEVEL_ONE_2;
		}
		break;

	case LEVEL_ONE_2:
		if (App->player2->power_up == 0) {
			state = NOT_EXISTING_2;
		}
		if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_REPEAT) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 300) {
				time_shoot = true;
				LOG("Change to charged");
				state = LEVEL_ONE_CHARGE_2;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_UP) {
			time_shoot = true;
		}
		break;
		
	case LEVEL_ONE_CHARGE_2:
		if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_UP) {
			spawn.Reset();
			spawn_reverse.Reset();
			state = SHOT;
		}
		break;

	case SHOT:
		if (App->player2->power_up == 0) {
			state = NOT_EXISTING_2;
		}
		if (time_mirror) {
			time_on_entry = SDL_GetTicks();
			time_mirror = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 4000) {
			state = DESPAWN;
		}
		break;

	case DESPAWN:
		if (spawn_reverse.Finished()) {
			spawn_reverse.Reset();
			movement = true;
			time_mirror = true;
			state = SPAWN;
		}
		break;
	}

	//Mirror 2
	switch (state_2) {
	case NOT_EXISTING_2:
		time_mirror_2 = true;
		if (App->player2->power_up == 2) {
			state_2 = SPAWN;
		}
		break;

	case SPAWN:
		if (spawn2.Finished()) {
			spawn2.Reset();
			state_2 = LEVEL_ONE_2;
		}
		break;

	case LEVEL_ONE_2:
		if (App->player2->power_up <= 1) {
			state_2 = NOT_EXISTING_2;
		}
		if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_REPEAT) {
			if (time_shoot_2) {
				time_on_entry_2 = SDL_GetTicks();
				time_shoot_2 = false;
			}
			current_time_2 = SDL_GetTicks() - time_on_entry_2;
			if (current_time_2 > 300) {
				time_shoot_2 = true;
				state_2 = LEVEL_ONE_CHARGE_2;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_UP) {
			time_shoot_2 = true;
		}
		break;

	case LEVEL_ONE_CHARGE_2:
		if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_UP) {
			spawn2.Reset();
			spawn_reverse2.Reset();
			state_2 = SHOT;
		}
		break;

	case SHOT:
		if (App->player2->power_up <= 1) {
			state_2 = NOT_EXISTING_2;
		}
		if (time_mirror_2) {
			time_on_entry_2 = SDL_GetTicks();
			time_mirror_2 = false;
		}
		current_time_2 = SDL_GetTicks() - time_on_entry_2;
		if (current_time_2 > 4000) {
			state_2 = DESPAWN;
		}
		break;

	case DESPAWN:
		if (spawn_reverse2.Finished()) {
			spawn_reverse2.Reset();
			time_mirror_2 = true;
			state_2 = SPAWN;
		}
		break;

	}
}
void ModulePartner2::PerformActions()
{
	//Mirror 1
	switch (state) {
	case NOT_EXISTING_2:
		current_animation = &iddle;
		exist = false;
		break;

	case SPAWN:
		current_animation = &spawn;
		exist = true;
		break;

	case LEVEL_ONE_2:
		current_animation = &iddle;
		exist = true;
		break;

	case LEVEL_ONE_CHARGE_2:
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

	case DESPAWN:
		current_animation = &spawn_reverse;
		break;

	case SHOT:
		current_animation = &iddle;
		break;

	}

	//Mirror 2
	switch (state_2) {
	case NOT_EXISTING_2:
		current_animation_2 = &iddle2;
		exist_2 = false;
		break;

	case SPAWN:
		current_animation_2 = &spawn2;
		exist_2 = true;
		break;

	case LEVEL_ONE_2:
		current_animation_2 = &iddle2;
		exist_2 = true;
		break;

	case LEVEL_ONE_CHARGE_2:
		if (!spawn_reverse2.Finished()) {
			current_animation_2 = &spawn_reverse2;
		}
		if (spawn_reverse2.Finished() && !spawn2.Finished()) {
			current_animation_2 = &spawn2;
		}
		if (spawn_reverse2.Finished() && spawn2.Finished()) {
			current_animation_2 = &charging2;
		}
		break;

	case DESPAWN:
		current_animation_2 = &spawn_reverse2;
		break;

	case SHOT:
		current_animation_2 = &iddle2;
		break;


	}


}
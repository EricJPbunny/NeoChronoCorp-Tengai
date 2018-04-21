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
		LOG("Could not unload partner textures")
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

	//Draw Partner
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect r1 = current_animation_2->GetCurrentFrame();
	if (exist) {
		App->render->Blit(graphics, position.x + 10, position.y - 10 - r.h, &r);
	}
	if (exist_2) {
		App->render->Blit(graphics, position.x+5, position.y+5 - r1.h, &r1);
	}
	
	return UPDATE_CONTINUE;
}

void ModulePartner2::CheckState() 
{
	//Mirror 1
	switch (state) {
	case NOT_EXISTING_2:
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
		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_REPEAT) {
			state = LEVEL_ONE_CHARGE_2;
		}
		break;
		
	case LEVEL_ONE_CHARGE_2:
		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_UP) {
			spawn.Reset();
			spawn_reverse.Reset();
			state = SHOT;
			movement = true;
		}
		break;

	case SHOT:
		if (iddle.GetCurrentLoop() > 30) {
			state = SPAWN;
		}
		break;
	}

	//Mirror 2
	switch (state_2) {
	case NOT_EXISTING_2:
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
		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_REPEAT) {
			state_2 = LEVEL_ONE_CHARGE_2;
		}
		break;

	case LEVEL_ONE_CHARGE_2:
		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_UP) {
			spawn2.Reset();
			spawn_reverse2.Reset();
			state_2 = SHOT;
			movement = true;
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
			current_animation = &spawn;
			position.x = App->player2->position.x +25;
			position.y = App->player2->position.y - 20;
			movement = false;
		}
		if (spawn_reverse.Finished() && spawn.Finished()) {
			current_animation = &charging;
			position.x = App->player2->position.x + 25;
			position.y = App->player2->position.y - 20;
			movement = false;
		}
		break;

	case SHOT:
		current_animation = &iddle;
		position.x = App->player2->position.x + 25;
		position.y = App->player2->position.y - 20;
		movement = false;

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
			position.x = App->player2->position.x + 25;
			position.y = App->player2->position.y - 20;
			movement = false;
		}
		if (spawn_reverse2.Finished() && spawn2.Finished()) {
			current_animation_2 = &charging2;
			position.x = App->player2->position.x + 25;
			position.y = App->player2->position.y - 20;
			movement = false;
		}


	}


}
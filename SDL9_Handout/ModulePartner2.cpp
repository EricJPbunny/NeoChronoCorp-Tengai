#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePartner2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneForest.h"
#include "ModulePlayer2.h"
#include "ModuleUI.h"


ModulePartner2::ModulePartner2()
{
	graphics = nullptr;
	current_animation = nullptr;

	spawn.PushBack({10,149,3,5});
	spawn.PushBack({ 18,149,4,5 });
	spawn.PushBack({ 32,147,9,9 });
	spawn.PushBack({ 51,147,10,11 });
	spawn.speed = 0.15f;

	iddle.PushBack({ 123,175,15,13 });
	iddle.PushBack({ 148,175,15,13 });
	iddle.PushBack({ 171,175,15,13 });
	iddle.PushBack({ 193,175,15,13 });
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
	position.x = App->player2->position.x - 20;
	position.y = App->player2->position.y + 20;
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
	//Draw Partner
	SDL_Rect r = current_animation->GetCurrentFrame();
	
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}

void ModulePartner2::CheckState() 
{
	switch (state) {
	case NOT_EXISTING_2:
		if (App->player2->power_up == 1) {
			state = LEVEL_ONE_2;
		}
		break;

	case LEVEL_ONE_2:
		if (App->player2->power_up == 0) {
			state = NOT_EXISTING_2;
		}
		if (App->player2->power_up == 2) {
			state = LEVEL_TWO_2;
		}
		break;
	case LEVEL_TWO_2:
		if (App->player2->power_up == 1) {
			state = LEVEL_ONE_2;
		}
		break;
	}
}
void ModulePartner2::PerformActions()
{
	switch (state) {
	case NOT_EXISTING_2:
		current_animation = &iddle;
		exist = false;
		break;

	case LEVEL_ONE_2:
		exist = true;
		current_animation = &iddle;
		break;
		
	case LEVEL_TWO_2:
		current_animation = &iddle2;
		break;
	}


}
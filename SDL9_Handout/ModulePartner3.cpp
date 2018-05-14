#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneAir.h"
//#include "ModulePlayer3.h"
#include "ModulePartner3.h"
#include "ModuleUI.h"


#include "SDL\include\SDL_timer.h"

ModulePartner3::ModulePartner3()
{
	graphics = nullptr;
	current_animation = nullptr;

	/*spawn.PushBack
	spawn.PushBack
	spawn.PushBack
	spawn.PushBack
	spawn.speed

	iddle.PushBack
	iddle.PushBack
	iddle.PushBack
	iddle.PushBack
	iddle.speed

	charging.PushBack
	charging.PushBack
	charging.PushBack
	charging.speed

	decharging.PushBack
	decharging.PushBack
	decharging.PushBack
	decharging.PushBack
	decharging.speed

	charged.PushBack
	charged.PushBack
	charged.PushBack
	charged.PushBack
	charged.speed */

}

ModulePartner3::~ModulePartner3()
{
	//destroyer
}

bool ModulePartner3::Start()
{
	LOG("Loading partner textures");
	//cridar path de les textures (graphics=...)
	if (graphics == nullptr)
	{
		LOG("Could not load partner textures")
			return false;
	}

	/*position.x = App->player3->position.x - 20;
	position.y = App->player3->position.y + 20;*/
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

	//Draw partner
	SDL_Rect r = current_animation->GetCurrentFrame();

	//Set position
	/*position.x = App->player3->position.x - 20;
	position.y = App->player3->position.y - 20;*/
}


void ModulePartner3::CheckState()
{

}


void ModulePartner3::PerformActions()
{

}
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleUlti3.h"
#include "ModulePlayer3.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"

ModuleUlti3::ModuleUlti3()
{
	petal_1.anim.PushBack({ 466,380,23,26 });
	petal_1.anim.PushBack({ 674,380,23,25 });
	petal_1.anim.PushBack({ 535,428,27,20 });
	petal_1.anim.PushBack({ 453,335,21,23 });
	petal_1.anim.PushBack({ 579,338,21,24 });
	petal_1.anim.PushBack({ 490,427,21,23 });
	petal_1.anim.PushBack({ 538,382,27,26 });
	petal_1.anim.PushBack({ 421,340,22,26 });
	petal_1.life = 3000;
	petal_1.anim.speed = 0.20f;
	petal_1.speed = { 2, -2 };
}

ModuleUlti3::~ModuleUlti3()
{}

// Load assets
bool ModuleUlti3::Start()
{
	LOG("Loading Ulti 3");
	graphics = App->textures->Load("assets/sprite/Sho_Spritesheet.png");
	return true;
}

// UnLoad assets
bool ModuleUlti3::CleanUp()
{
	LOG("Unloading Ulti 3");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleUlti3::Update()
{
	if (timer) {
		time_on_entry = SDL_GetTicks();
		timer = false;
	}
	current_time = SDL_GetTicks() - time_on_entry;
	if(current_time > 4000){
		if (interval) {
			interval_on_entry = SDL_GetTicks();
			interval = false;
		}
		current_interval = SDL_GetTicks() - interval_on_entry;
		if (current_interval > 500) {
			App->particles->AddParticle(petal_1, (App->render->camera.x / SCREEN_SIZE) + 10, (App->render->camera.y / SCREEN_SIZE) + 190);
			interval = true;
		}
	}
	

	return UPDATE_CONTINUE;
}
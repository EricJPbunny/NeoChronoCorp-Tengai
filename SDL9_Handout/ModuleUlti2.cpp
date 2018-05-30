#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleUlti2.h"
#include "ModulePlayer2.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"

ModuleUlti2::ModuleUlti2()
{
	sword.anim.PushBack({ 177,122,64,9 });
	sword.anim.PushBack({ 247,119,64,9 });
	sword.anim.PushBack({ 323,119,64,9 });
	sword.anim.PushBack({ 389,119,64,9 });
	sword.anim.PushBack({ 453,119,64,9 });
	sword.anim.speed = 0.30f;
	sword.anim.loop = true;
	sword.life = 2800;
	sword.speed.x = 4.00f;

	sword_idle.anim.PushBack({ 520,119,64,9 });
	sword_idle.anim.speed = 0.30f;
	sword_idle.anim.loop = true;
	sword_idle.life = 2800;
	sword_idle.speed.x = 4.00f;

}

ModuleUlti2::~ModuleUlti2()
{}

// Load assets
bool ModuleUlti2::Start()
{
	LOG("Loading Ulti 2");
	graphics = App->textures->Load("assets/sprite/Sho_Spritesheet.png");
	return true;
}

// UnLoad assets
bool ModuleUlti2::CleanUp()
{
	LOG("Unloading Ulti 2");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleUlti2::Update()
{
	LOG("ULTI");
	if (timer) {
		time_on_entry = SDL_GetTicks();
		timer = false;
		interval = true;
	}
	if (interval) {
		interval_on_entry = SDL_GetTicks();
		interval = false;
	}
	current_interval = SDL_GetTicks() - interval_on_entry;
	switch (random) {
	case 1:
		aux = 10;
		break;
	case 2:
		aux = 20;
		break;
	case 3:
		aux = -10;
		break;
	case 4:
		aux = 0;
		random = 0;
		break;
	}
	if (current_interval > 400) {
		App->particles->AddParticle(sword_idle, (App->render->camera.x  / SCREEN_SIZE) + 10, (App->render->camera.y / SCREEN_SIZE) + 30 + aux, COLLIDER_PLAYER_2_SHOT);
		App->particles->AddParticle(sword_idle, (App->render->camera.x / SCREEN_SIZE) + 15, (App->render->camera.y / SCREEN_SIZE) + 100 + aux, COLLIDER_PLAYER_2_SHOT);
		App->particles->AddParticle(sword_idle, (App->render->camera.x / SCREEN_SIZE) + 10, (App->render->camera.y / SCREEN_SIZE) + 190 + aux, COLLIDER_PLAYER_2_SHOT);
		interval = true;
		random++;
	}
	current_time = SDL_GetTicks() - time_on_entry;
	if (current_time > 3000) {
		LOG("Disabled");
		App->ulti2->Disable();
	}

	return UPDATE_CONTINUE;
}
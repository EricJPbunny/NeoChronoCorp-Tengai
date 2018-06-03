#include <iostream>
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
	sword.anim.PushBack({ 520,119,64,9 });
	sword.anim.speed = 0.30f;
	sword.anim.loop = false;
	sword.life = 3000;
	sword.speed.x = 4.00f;

	ulti_collider.x = 0;
	ulti_collider.y = 0;
	ulti_collider.w = SCREEN_WIDTH;
	ulti_collider.h = SCREEN_HEIGHT;
}

ModuleUlti2::~ModuleUlti2()
{}

// Load assets
bool ModuleUlti2::Start()
{
	LOG("Loading Ulti 2");
	graphics = App->textures->Load("assets/sprite/Sho_Spritesheet.png");
	coll = App->collision->AddCollider(ulti_collider, COLLIDER_ULTI2);
	ulti_fx = App->audio->LoadEffect("assets/audio/sho ulti.wav");
	App->audio->PlaySoundEffects(ulti_fx);
	
	return true;
}

// UnLoad assets
bool ModuleUlti2::CleanUp()
{
	LOG("Unloading Ulti 2");
	if (coll != nullptr)
		coll->to_delete = true;
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
		random = rand() % 8;
		current_interval = SDL_GetTicks() - interval_on_entry;
		switch (random) {
		case 0:
			aux = -5;
			break;
		case 1:
			aux = 10;
			break;
		case 2:
			aux = 20;
			break;
		case 3:
			aux = -20;
			break;
		case 4:
			aux = 0;
			break;
		case 5:
			aux = -30;
			break;
		case 6:
			aux = -15;
			break;
		case 7:
			aux = 30;
			break;
		}

		if (current_interval > 400) {
			App->particles->AddParticle(sword, (App->render->camera.x / SCREEN_SIZE) + 10, (App->render->camera.y / SCREEN_SIZE) + 30 + aux);
			App->particles->AddParticle(sword, (App->render->camera.x / SCREEN_SIZE) + 15, (App->render->camera.y / SCREEN_SIZE) + 100 + aux);
			App->particles->AddParticle(sword, (App->render->camera.x / SCREEN_SIZE) + 10, (App->render->camera.y / SCREEN_SIZE) + 190 + aux);
			interval = true;
			random++;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 7000) {
			LOG("Disabled");
			App->ulti2->Disable();
		}

		if(timer_1){
			time_on_entry_1 = SDL_GetTicks();
			timer_1 = false;
		}
		current_time_1 = SDL_GetTicks() - time_on_entry_1;
		if (current_time_1 > 120) {
			coll->SetPos((App->render->camera.x / SCREEN_SIZE), (App->render->camera.y / SCREEN_SIZE));
			timer_1 = true;
		}
		else {
			coll->SetPos(-2000, -2000);
		}

		return UPDATE_CONTINUE;
}
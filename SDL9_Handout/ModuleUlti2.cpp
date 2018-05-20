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
	sword.anim.loop = false;
	sword.life = 2800;
	sword.speed.x = 1.00f;

	sword_idle.anim.PushBack({ 520,119,64,9 });
	sword.anim.speed = 0.30f;
	sword.anim.loop = true;
	sword.life = 2800;
	sword.speed.x = 8.00f;

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
	if (timer) {
		time_on_entry = SDL_GetTicks();
		timer = false;
		if (sword.anim.Finished()) {
			App->particles->AddParticle(sword_idle, App->player2->position.x, 30, COLLIDER_PLAYER_2_SHOT);
		}
		else{ 
			App->particles->AddParticle(sword_idle, App->player2->position.x, 30, COLLIDER_PLAYER_2_SHOT); 
		}

	
	}
	current_time = SDL_GetTicks() - time_on_entry;
	if (current_time > 3000) {
		timer = true;
		LOG("Disabled");
		App->ulti2->Disable();
	}

	return UPDATE_CONTINUE;
}
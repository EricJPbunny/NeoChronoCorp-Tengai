#include "Globals.h"
#include "Application.h"
#include "ModuleBackground.h"
#include "ModuleScore.h"
#include "ModuleLevel2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL_render.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel2::ModuleLevel2()
{
	//2nd Level
	lev2.x = 0;
	lev2.y = 0;
	lev2.w = SCREEN_WIDTH;
	lev2.h = SCREEN_HEIGHT;
}

ModuleLevel2::~ModuleLevel2()
{}

// Load assets
bool ModuleLevel2::Start()
{
	LOG("Loading Level 2");
	bool ret = true;
	graphics = App->textures->Load("2ndlevel.png");

	mus = App->audio->LoadMusic("03_Sky_dance.ogg");

	Mix_PlayMusic(mus, -1);

 	App->player->Enable();
	return ret;
}

// Load assets
bool ModuleLevel2::CleanUp()
{
	LOG("Unloading Level 2");

	App->player->Disable();
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleLevel2::Update()
{
	// Draw everything --------------------------------------	
	
	App->render->Blit(graphics, 0, 0, &lev2, 0.00f);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->level2, App->scores, 0.60f);
	}

	return UPDATE_CONTINUE;
}
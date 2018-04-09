#include "Globals.h"
#include "Application.h"
#include "ModuleScore.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL_render.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleIntro.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleScore::ModuleScore()
{
	//2nd Level
	score.x = 0;
	score.y = 0;
	score.w = SCREEN_WIDTH;
	score.h = SCREEN_HEIGHT;
}

ModuleScore::~ModuleScore()
{}

// Load assets
bool ModuleScore::Start()
{
	LOG("Loading Score");
	bool ret = true;
	graphics = App->textures->Load("Score.png");

	mus = App->audio->LoadMusic("20_The_king_is_evil_too.ogg");


	return ret;
}

// Load assets
bool ModuleScore::CleanUp()
{
	LOG("Unloading Score");

	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleScore::Update()
{
	// Draw everything --------------------------------------	
	
	App->render->Blit(graphics, 0, 0, &score, 0.00f);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->scores, App->intro, 0.60f);
	}

	return UPDATE_CONTINUE;
}
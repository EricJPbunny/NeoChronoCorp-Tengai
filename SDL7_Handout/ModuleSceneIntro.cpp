#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneStart.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_render.h"


ModuleSceneIntro::ModuleSceneIntro()
{
	// Psikyo
	Psikyo.x = 0;
	Psikyo.y = 0;
	Psikyo.w = SCREEN_WIDTH;
	Psikyo.h = SCREEN_HEIGHT;

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro");

	graphics = App->textures->Load("assets/sprite/Psikyo.png");

	mus = App->audio->LoadMusic("assets/audio/Psikyo_intro.ogg");

	App->audio->PlayMusic(mus,1);

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro");

	App->audio->UnloadMusic(mus);
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &Psikyo, 0.00f);

	// If pressed, change scene
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(App->scene_intro, App->scene_start, 0.60f);
	}

	return UPDATE_CONTINUE;
}
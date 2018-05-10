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
#include "SDL/include/SDL_timer.h"


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
	start = App->audio->LoadEffect("assets/audio/Intro.wav");

	App->audio->PlayMusic(mus,1);

	time_on_entry = SDL_GetTicks();

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro");

	App->audio->UnloadMusic(mus);
	App->textures->Unload(graphics);
	App->audio->UnloadFx(start);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Timer
	current_time = SDL_GetTicks() - time_on_entry;
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &Psikyo, 0.00f);

	// If pressed, change scene
	if (App->input->keyboard[SDL_SCANCODE_RETURN]==KEY_STATE::KEY_DOWN || current_time>8000 || App->input->controller_START_button == KEY_STATE::KEY_DOWN) {
		App->audio->PlaySoundEffects(start);
		App->fade->FadeToBlack(App->scene_intro, App->scene_start, 0.50f);
	}

	return UPDATE_CONTINUE;
}
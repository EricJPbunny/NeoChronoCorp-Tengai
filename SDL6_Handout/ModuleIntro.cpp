#include "Globals.h"
#include "Application.h"
#include "ModuleBackground.h"
#include "ModuleTextures.h"
#include "ModuleIntro.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_render.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleIntro::ModuleIntro()
{
	// Psikyo
	Psikyo.x = 0;
	Psikyo.y = 0;
	Psikyo.w = SCREEN_WIDTH;
	Psikyo.h = SCREEN_HEIGHT;

}

ModuleIntro::~ModuleIntro()
{}

// Load assets
bool ModuleIntro::Start()
{
	LOG("Loading Intro");
	
	graphics = App->textures->Load("assets/sprite/Psikyo.png");

	//mus = App->audio->LoadMusic("assets/audio/Psikyo_intro.ogg");

	//App->audio->PlayMusic(mus,1);

	return true;
}

// UnLoad assets
bool ModuleIntro::CleanUp()
{
	LOG("Unloading Intro");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleIntro::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &Psikyo, 0.00f);

	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(App->intro, App->background, 0.60f);
	}
	
	return UPDATE_CONTINUE;
}
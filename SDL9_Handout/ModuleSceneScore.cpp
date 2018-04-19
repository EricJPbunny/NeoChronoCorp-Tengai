#include "Globals.h"
#include "Application.h"
#include "ModuleSceneScore.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL_render.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleSceneStart.h"

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
	graphics = App->textures->Load("assets/sprite/Score.png");
	font_score = App->fonts->Load("fonts/score_fonts1.png", "0123456789", 1);
	mus = App->audio->LoadMusic("assets/audio/20_The_king_is_evil_too.ogg");

	App->audio->PlayMusic(mus);
	return ret;
}

// Load assets
bool ModuleScore::CleanUp()
{
	LOG("Unloading Score");
	App->audio->UnloadMusic(mus);
	App->fonts->UnLoad(font_score);
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleScore::Update()
{
	// Draw everything --------------------------------------	
	
	App->render->Blit(graphics, 0, 0, &score, 0.00f);

	App->fonts->BlitText(217, 67, App->ui->font_score, App->ui->player1_score);
	App->fonts->BlitText(217, 147, App->ui->font_score, App->ui->player2_score);
	
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(App->scene_score, App->scene_start, 0.60f);
	}

	return UPDATE_CONTINUE;
}
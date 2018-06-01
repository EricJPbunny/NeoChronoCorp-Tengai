#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneSelect.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_render.h"


ModuleSceneSelect::ModuleSceneSelect()
{
	//Select Screen
	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 224;

	sho_face.x = 0;
	sho_face.y = 224;
	sho_face.w = 112;
	sho_face.h = 129;

	junis_face.x = 113;
	junis_face.y = 224;
	junis_face.w = 110;
	junis_face.h = 129;

	sho_player.x = 1;
	sho_player.y = 354;
	sho_player.w = 153;
	sho_player.h = 123;

	junis_player.x = 161;
	junis_player.y = 354;
	junis_player.w = 127;
	junis_player.h = 109;

	ui_1p.x = 230;
	ui_1p.y = 292;
	ui_1p.w = 46;
	ui_1p.h = 53;

	ui_2p.x = 278;
	ui_2p.y = 292;
	ui_2p.w = 46;
	ui_2p.h = 53;

	junis_name.x = 230;
	junis_name.y = 260;
	junis_name.w = 80;
	junis_name.h = 30;

	sho_name.x = 229;
	sho_name.y = 225;
	sho_name.w = 62;
	sho_name.h = 32;

	time.x = 298;
	time.y = 229;
	time.w = 29;
	time.h = 9;

}

ModuleSceneSelect::~ModuleSceneSelect()
{}

// Load assets
bool ModuleSceneSelect::Start()
{
	LOG("Loading Start Screen");
	App->render->camera.x = 0;
	graphics = App->textures->Load("assets/sprite/Select_Screen.png");

	return true;
}

// UnLoad assets
bool ModuleSceneSelect::CleanUp()
{
	LOG("Unloading Start Screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleSceneSelect::Update()
{
	//Print screen
	App->render->Blit(graphics, 0, 0, &background);

	// If pressed, change scene
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN|| App->input->controller_START_button == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(App->scene_select, App->scene_air, 1.50f);
	}

	return UPDATE_CONTINUE;
}
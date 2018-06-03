#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneSelect.h"
#include "ModuleSceneStart.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_timer.h"
#include "SDL\include\SDL_render.h"
#include <string>


ModuleSceneSelect::ModuleSceneSelect()
{
	//Select Screen
	background_1p.x = 0;
	background_1p.y = 0;
	background_1p.w = 320;
	background_1p.h = 224;

	background_2p.x = 455;
	background_2p.y = 0;
	background_2p.w = 320;
	background_2p.h = 224;

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

	sho_sprite.PushBack({332,40,31,27});
	sho_sprite.PushBack({ 369,40,31,27 });
	sho_sprite.PushBack({ 406,41,31,27 });
	sho_sprite.loop = true;
	sho_sprite.speed = 0.30f;

	junis_sprite.PushBack({ 331,7,28,27 });
	junis_sprite.PushBack({ 373,8,28,27 });
	junis_sprite.PushBack({ 416,9,28,27 });
	junis_sprite.loop = true;
	junis_sprite.speed = 0.30f;

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

	credit.x = 323;
	credit.y = 71;
	credit.w = 40;
	credit.h = 7;

}

ModuleSceneSelect::~ModuleSceneSelect()
{}

// Load assets
bool ModuleSceneSelect::Start()
{
	LOG("Loading Start Screen");
	App->render->camera.x = 0;
	graphics = App->textures->Load("assets/sprite/Select_Screen.png");
	font_time = App->fonts->Load("fonts/time_fonts.png", "0123456789", 1);
	font_score = App->fonts->Load("fonts/score_fonts.png", "0123456789", 1);

	change_player = App->audio->LoadEffect("assets/audio/select_player.wav");
	select_sho = App->audio->LoadEffect("assets/audio/select_sho.wav");
	select_junis = App->audio->LoadEffect("assets/audio/select_junis.wav");

	App->scene_start->credit_num--;

	return true;
}

// UnLoad assets
bool ModuleSceneSelect::CleanUp()
{
	LOG("Unloading Start Screen");

	App->audio->UnloadFx(select_junis);
	App->audio->UnloadFx(select_sho);
	App->audio->UnloadFx(change_player);
	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_time);
	App->fonts->UnLoad(font_score);
	return true;
}

// Update: draw background
update_status ModuleSceneSelect::Update()
{
	//Time
	sprintf_s(time_text, 2, "%1d", time_num);
	sprintf_s(credit_text, 3, "%1d", App->scene_start->credit_num);

	if (timer) {
		time_on_entry = SDL_GetTicks();
		timer = false;
	}
	current_time = SDL_GetTicks() - time_on_entry;
	if (current_time > 1000) {
		time_num--;
		timer = true;
	}

	//Player 1 vs Player 2
	if (one_player) {
		if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN && App->scene_start->credit_num > 0) {
			App->scene_start->credit_num--;
			one_player = false;
		}
	}

	if (App->scene_start->credit_num < 9) {
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->controller_B_button == KEY_STATE::KEY_DOWN || App->input->controller_B_button2 == KEY_STATE::KEY_DOWN) {
			App->scene_start->credit_num++;
		}
	}

	//Get Current Animations
	junis_anim = junis_sprite.GetCurrentFrame();
	sho_anim = sho_sprite.GetCurrentFrame();

	//Print screen
	if (one_player) {
		App->render->Blit(graphics, 0, 0, &background_1p);
		if (sho_p1) {
			App->render->Blit(graphics, 18, 158, &ui_1p);
			App->render->Blit(graphics, 16, 16, &sho_face);
			App->render->Blit(graphics, 42, 121, &sho_name);
			App->render->Blit(graphics, 146, 20, &sho_player);
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN) {
				App->audio->PlaySoundEffects(change_player);
				sho_p1 = false;
			}
		}
		else {
			App->render->Blit(graphics, 65, 158, &ui_1p);
			App->render->Blit(graphics, 18, 16, &junis_face);
			App->render->Blit(graphics, 33, 122, &junis_name);
			App->render->Blit(graphics, 160, 34, &junis_player);
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) {
				App->audio->PlaySoundEffects(change_player);
				sho_p1 = true;
			}
		}
	}
	else {
		App->render->Blit(graphics, 0, 0, &background_2p);
		if (sho_p1) {
			App->render->Blit(graphics, 18, 158, &ui_1p);
			App->render->Blit(graphics, 65, 158, &ui_2p);
			App->render->Blit(graphics, 2, 20, &sho_player);
			App->render->Blit(graphics, 176, 34, &junis_player);
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN) {
				sho_p1 = false;
			}
		}
		else {
			App->render->Blit(graphics, 18, 158, &ui_2p);
			App->render->Blit(graphics, 65, 158, &ui_1p);
			App->render->Blit(graphics, 16, 34, &junis_player);
			App->render->Blit(graphics, 162, 20, &sho_player);
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN) {
				sho_p1 = true;
			}
		}
	}
	App->render->Blit(graphics, 25, 172, &sho_anim);
	App->render->Blit(graphics, 75, 172, &junis_anim);

	App->render->Blit(graphics, 138, 214, &time);
	App->fonts->BlitText(154, 210, font_time, time_text);

	App->render->Blit(graphics, 255, 216, &credit, 0.00f, 0.00f);
	App->fonts->BlitText(290, 214, font_score, credit_text);

	// If pressed, change scene
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || App->input->controller_START_button == KEY_STATE::KEY_DOWN || time_num == 0) {
		if (sho_p1) {
			App->audio->PlaySoundEffects(select_sho);
		}
		else {
			App->audio->PlaySoundEffects(select_junis);
		}
		App->fade->FadeToBlack(App->scene_select, App->scene_air, 0.90f);
	}

	return UPDATE_CONTINUE;
}


#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneScore.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayer3.h"
#include "ModuleSceneSelect.h"
#include "ModuleSceneStart.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"
#include <string>


ModuleUI::ModuleUI()
{
	player1.x = 8;
	player1.y = 6;
	player1.w = 15;
	player1.h = 9;

	player2.x = 26;
	player2.y = 6;
	player2.w = 16;
	player2.h = 9;

	//Start Animation
	start.PushBack({ 44,150,67,15 });
	start.PushBack({ 5,50,67,15 });
	start.PushBack({});
	start.speed = 0.03f;

	game_over.x = 116;
	game_over.y = 153;
	game_over.w = 123;
	game_over.h = 38;

	screen.x = 0;
	screen.y = 0;
	screen.w = SCREEN_WIDTH;
	screen.h = SCREEN_HEIGHT;

	life_koyori.x = 4;
	life_koyori.y = 173;
	life_koyori.w = 16;
	life_koyori.h = 14;

	life_sho.x = 24;
	life_sho.y = 174;
	life_sho.w = 15;
	life_sho.h = 13;

	life_junis.x = 43;
	life_junis.y = 174;
	life_junis.w = 13;
	life_junis.h = 13;

	credit.x = 63;
	credit.y = 173;
	credit.w = 40;
	credit.h = 7;

	ulti_parchment.PushBack({ 8,19,14,16 });
	ulti_parchment.PushBack({ 24,19,14,16 });
	ulti_parchment.speed = 0.10f;

}

ModuleUI::~ModuleUI()
{}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading UI");
	time = 9;
	graphics = App->textures->Load("assets/sprite/UI.png");
	black = App->textures->Load("assets/sprite/black.png");
	font_score = App->fonts->Load("fonts/score_fonts.png", "0123456789", 1);
	font_time = App->fonts->Load("fonts/time_fonts.png", "0123456789", 1);
	return true;
}

// UnLoad assets
bool ModuleUI::CleanUp()
{
	LOG("Unloading UI");
	App->fonts->UnLoad(font_time);
	App->fonts->UnLoad(font_score);
	App->textures->Unload(black);
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleUI::Update()
{
	//Draw UI Score
	sprintf_s(player1_score, 10, "%1d", score_koyori);
	sprintf_s(player2_score, 10, "%1d", score_sho);
	sprintf_s(player3_score, 10, "%1d", score_junis);

	sprintf_s(credit_text, 3, "%1d", App->scene_start->credit_num);

	sprintf_s(time_text, 2, "%1d", time);
	
	//Draw Top UI Interface
	current_animation = &start;
	ulti_ui = &ulti_parchment;
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect ulti = ulti_ui->GetCurrentFrame();

	//Player1: Sho
	if (!game_over_sho && App->player2->IsEnabled()) {
		if (App->scene_select->sho_p1) {
			App->render->Blit(graphics, 10, 6, &player1, 0.00f, 0.00f);
			App->fonts->BlitText(18, 5, font_score, player2_score);
			//Life Sho
			for (int i = 1; i <= num_life_sho - 1; i++) {
				App->render->Blit(graphics, 76 + life_sho.w*i, 1, &life_sho, 0.00f, 0.00f);
			}
			//Ulti Sho
			for (int i = 0; i <= num_ulti_sho - 1; i++) {
				App->render->Blit(graphics, 8 + 14*i, 15, &ulti, 0.00f, 0.00f);
			}
		}
		else {
			App->render->Blit(graphics, 170, 5, &player2, 0.00f, 0.00f);
			App->fonts->BlitText(180, 5, font_score, player2_score);
			//Life Sho
			for (int i = 1; i <= num_life_sho - 1; i++) {
				App->render->Blit(graphics, 236 + life_sho.w*i, 1, &life_sho, 0.00f, 0.00f);
			}
			//Ulti Sho
			for (int i = 0; i <= num_ulti_sho - 1; i++) {
				App->render->Blit(graphics, 170 + 14 * i, 15, &ulti, 0.00f, 0.00f);
			}
		}
	}
	else {
		if (App->scene_select->sho_p1) {
			App->render->Blit(graphics, 35, 10, &r, 0.00f, 0.00f);
		}
		else {
			App->render->Blit(graphics, 210, 10, &r, 0.00f, 0.00f);
		}
	}

	//Player2: Junis
	if (!game_over_junis && App->player3->IsEnabled()) {
		if (!App->scene_select->sho_p1) {
			App->render->Blit(graphics, 10, 6, &player1, 0.00f, 0.00f);
			App->fonts->BlitText(18, 5, font_score, player3_score);
			//Life Junis
			for (int i = 1; i <= num_life_junis - 1; i++) {
				App->render->Blit(graphics, 76 + life_junis.w*i, 1, &life_junis, 0.00f, 0.00f);
			}
			//Ulti Junis
			for (int i = 0; i <= num_ulti_junis - 1; i++) {
				App->render->Blit(graphics, 8 + 14 * i, 15, &ulti, 0.00f, 0.00f);
			}
		}
		else {
			App->render->Blit(graphics, 170, 5, &player2, 0.00f, 0.00f);
			App->fonts->BlitText(180, 5, font_score, player3_score);
			//Life Junis
			for (int i = 1; i <= num_life_junis - 1; i++) {
				App->render->Blit(graphics, 236 + life_junis.w*i, 1, &life_junis, 0.00f, 0.00f);
			}
			//Ulti Junis
			for (int i = 0; i <= num_ulti_junis - 1; i++) {
				App->render->Blit(graphics, 170 + 14 * i, 15, &ulti, 0.00f, 0.00f);
			}
		}
	}
	else {
		if (!App->scene_select->sho_p1) {
			App->render->Blit(graphics, 35, 10, &r, 0.00f, 0.00f);
		}
		else {
			App->render->Blit(graphics, 210, 10, &r, 0.00f, 0.00f);
		}
	}

	//

	//Game over
	SDL_SetTextureAlphaMod(black, alpha);

	if (game_over_sho && game_over_junis) {
		//Time countdown
		App->scene_air->speed = 0;
		App->scene_air->speedy = 0;
		if (aux) {
			time_on_entry = SDL_GetTicks();
			aux = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1000) {
			time--;
			aux = true;
		}

		//Disable
		enemies_movement = false;
		//Draw
		alpha = 100;
		App->render->Blit(black, 0, 0, &screen, 0.00f, 0.00f);
		App->render->Blit(graphics, 100, 90, &game_over, 0.00f, 0.00f);
		App->fonts->BlitText(180, 115, font_time, time_text);
		App->render->Blit(black, 0, 0, &screen, 0.00f, 0.00f);

		if (time == 0) {
			App->fade->FadeToBlack(App->scene_air, App->scene_score);
		}
	}
	
	App->render->Blit(graphics, 255, 216, &credit, 0.00f, 0.00f);
	App->fonts->BlitText(290, 214, font_score, credit_text);

	return UPDATE_CONTINUE;
}
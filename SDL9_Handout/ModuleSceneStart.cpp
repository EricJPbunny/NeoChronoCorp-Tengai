#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneStart.h"
#include "ModuleSceneSelect.h"
#include "ModuleUI.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "SDL\include\SDL_render.h"
#include <string>


ModuleSceneStart::ModuleSceneStart()
{
	//Background
	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 224;

	//Title
	title.x = 320;
	title.y = 0;
	title.w = 320;
	title.h = 224;

	//Press Start
	start.x = 0;
	start.y = 0;
	start.w = 320;
	start.h = 224;

	//Cloud 0
	cloud.x = 0;
	cloud.y = 224;
	cloud.w = 639;
	cloud.h = 44;

	//Cloud 1
	cloud1.x = 0;
	cloud1.y = 283;
	cloud1.w = 768;
	cloud1.h = 29;

	//Cloud 2
	cloud2.x = 0;
	cloud2.y = 314;
	cloud2.w = 384;
	cloud2.h = 31;

	//Cloud 3
	cloud3.x = 0;
	cloud3.y = 350;
	cloud3.w = 512;
	cloud3.h = 24;

	//Cloud 4
	cloud4.x = 0;
	cloud4.y = 379;
	cloud4.w = 513;
	cloud4.h = 10;

	//Cloud 5
	cloud5.x = 0;
	cloud5.y = 391;
	cloud5.w = 511;
	cloud5.h = 8;

	//Cloud 6
	cloud6.x = 0;
	cloud6.y = 404;
	cloud6.w = 507;
	cloud6.h = 8;

	//Cloud 7
	cloud7.x = 0;
	cloud7.y = 418;
	cloud7.w = 502;
	cloud7.h = 4;

	//Credit
	credit.x = 0;
	credit.y = 421;
	credit.w = 40;
	credit.h = 7;

}

ModuleSceneStart::~ModuleSceneStart()
{}

// Load assets
bool ModuleSceneStart::Start()
{
	LOG("Loading Start Screen");
	App->render->camera.x = 0;
	graphics = App->textures->Load("assets/sprite/start_screen.png");
	start_screen = App->textures->Load("assets/sprite/start.png");
	font_credit = App->fonts->Load("fonts/score_fonts.png", "0123456789", 1);
	intro = App->audio->LoadEffect("assets/audio/Intro.wav");
	add_credit = App->audio->LoadEffect("assets/audio/insert_coin.wav");

	return true;
}

// UnLoad assets
bool ModuleSceneStart::CleanUp()
{
	LOG("Unloading Start Screen");
	App->textures->Unload(graphics);
	App->textures->Unload(start_screen);
	App->fonts->UnLoad(font_credit);
	App->audio->UnloadFx(intro);
	return true;
}

// Update: draw background
update_status ModuleSceneStart::Update()
{
	//Credit
	sprintf_s(credit_text, 2, "%1d", credit_num);

	App->render->Blit(graphics, 0, 0, &background, 0.00f);

	//Eigth cloud
	posx14 -= 0.25f;
	if (posx14 <= -cloud7.w) {
		posx14 = 0;
	}
	posx15 = posx14;

	App->render->Blit(graphics, (int)posx14, 126, &cloud7);

	posx15 += cloud7.w;

	App->render->Blit(graphics, (int)posx15, 126, &cloud7);

	//Seventh cloud
	posx12 -= 0.50f;
	if (posx12 <= -cloud6.w) {
		posx12 = 0;
	}
	posx13 = posx10;

	App->render->Blit(graphics, (int)posx12, 126, &cloud6);


	posx13 += cloud6.w;

	App->render->Blit(graphics, (int)posx13, 126, &cloud6);

	//Sixth cloud
	posx10 -= 0.75f;
	if (posx10 <= -cloud5.w) {
		posx10 = 0;
	}
	posx11 = posx10;

	App->render->Blit(graphics, (int)posx10, 132, &cloud5);


	posx11 += cloud5.w;

	App->render->Blit(graphics, (int)posx11, 132, &cloud5);

	//Fifth cloud
	posx8 -= 1.00f;
	if (posx8 <= -cloud4.w) {
		posx8 = 0;
	}
	posx9 = posx8;

	App->render->Blit(graphics, (int)posx8, 138, &cloud4);


	posx9 += cloud4.w;

	App->render->Blit(graphics, (int)posx9, 138, &cloud4);

	//Fourth cloud
	posx6 -= 1.25;
	if (posx6 <= -cloud3.w) {
		posx6 = 0;
	}
	posx7 = posx6;

	App->render->Blit(graphics, (int)posx6, 146, &cloud3);

	posx7 += cloud3.w;

	App->render->Blit(graphics, (int)posx7, 146, &cloud3);

	//Third cloud
	posx4 -= 1.5;
	if (posx4 <= -cloud2.w) {
		posx4 = 0;
	}
	posx5 = posx4;

	App->render->Blit(graphics, (int)posx4, 150, &cloud2);

	posx5 += cloud2.w;

	App->render->Blit(graphics, (int)posx5, 150, &cloud2);

	//Second cloud
	posx2 -= 1.75f;
	if (posx2 <= -cloud1.w) {
		posx2 = 0;
	}
	posx3 = posx2;

	App->render->Blit(graphics, (int)posx2, 164, &cloud1);

	posx3 += cloud1.w;

	App->render->Blit(graphics, (int)posx3, 164, &cloud1);

	//First Cloud
	posx -= 2.00f;
	if (posx <= -cloud.w) {
		posx = 0;
	}

	posx1 = posx;

	App->render->Blit(graphics, posx, SCREEN_HEIGHT - cloud.h, &cloud);

	posx1 += cloud.w;

	App->render->Blit(graphics, posx1, SCREEN_HEIGHT - cloud.h, &cloud);

	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, 0, 0, &title);

	App->render->Blit(start_screen, 0, 0, &start);

	App->render->Blit(graphics, 120, 215, &credit);
	
	App->fonts->BlitText(152, 214, font_credit, credit_text);

	//Fader
	SDL_SetTextureAlphaMod(start_screen, alpha_start);

	if (alpha_start > SDL_ALPHA_TRANSPARENT && fade==true) {
		alpha_start -= 5;
	}
	else if(fade==true){
		alpha_start = 0;
		fade = false;
	}

	if (alpha_start < SDL_ALPHA_OPAQUE && fade==false) {
		alpha_start += 5;
	}
	else if(fade==false){
		alpha_start = 255;
		fade = true;
	}
	
	// Increase credit num
	if (credit_num < 9) {
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->controller_B_button == KEY_STATE::KEY_DOWN || App->input->controller_B_button2 == KEY_STATE::KEY_DOWN) {
			App->audio->PlaySoundEffects(add_credit);
			credit_num++;
		}
	}
	// If pressed, change scene
	if ((App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || App->input->controller_START_button == KEY_STATE::KEY_DOWN) && credit_num > 0) {
		App->audio->PlaySoundEffects(intro);
		App->fade->FadeToBlack(App->scene_start, App->scene_select, 0.90f);
	}

	return UPDATE_CONTINUE;
}
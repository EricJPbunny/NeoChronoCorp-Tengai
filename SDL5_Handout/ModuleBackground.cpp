#include "Globals.h"
#include "Application.h"
#include "ModuleBackground.h"
#include "ModuleIntro.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"	
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleLevel2.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

Background::Background()
{
	//Mid Fade
	fademid.x = 0;
	fademid.y = 0;
	fademid.w = SCREEN_WIDTH;
	fademid.h = SCREEN_HEIGHT;

	// Background / sky
	groundandtrees.x = 15;
	groundandtrees.y = 367;
	groundandtrees.w = 810;
	groundandtrees.h = 224;

	Templesgate.x = 2;
	Templesgate.y = 3;
	Templesgate.w = 150;
	Templesgate.h = 224;

	backtrees.x = 6;
	backtrees.y = 12;
	backtrees.w = 320;
	backtrees.h = 136;

	fisrttrees.x = 154;
	fisrttrees.y = 394;
	fisrttrees.w = 319;
	fisrttrees.h = 64;

	rockground.x = 828;
	rockground.y = 570;
	rockground.w = 160;
	rockground.h = 21;

	trees.x = 6;
	trees.y = 154;
	trees.w = 320;
	trees.h = 224;

	ground.x = 352;
	ground.y = 49;
	ground.w = 64;
	ground.h = 32;

	groundgrass.x = 990;
	groundgrass.y = 552;
	groundgrass.w = 165;
	groundgrass.h = 39;

	grasstrees2.x = 1158;
	grasstrees2.y = 367;
	grasstrees2.w = 256;
	grasstrees2.h = 224;

	grasstrees4.x = 1417;
	grasstrees4.y = 367;
	grasstrees4.w = 672;
	grasstrees4.h = 224;


	//Long Temple
	Temple.x = 174;
	Temple.y = 166;
	Temple.w = 348;
	Temple.h = 61;

	//Big Temple
	Temple2.x = 176;
	Temple2.y = 3;
	Temple2.w = 155;
	Temple2.h = 109;

	//lonely tree
	lonelytree.x = 612;
	lonelytree.y = 25;
	lonelytree.w = 25;
	lonelytree.h = 280;

	//Backgronund before Scroll Lateral
	backfinal.x = 0;
	backfinal.y = 0;
	backfinal.w = 320;
	backfinal.h = 224;

	//Tree's Top
	toptree.x = 8;
	toptree.y = 445;
	toptree.w = 15;
	toptree.h = 14;


	//Three Tree's Top
	toptrees.x = 13;
	toptrees.y = 398;
	toptrees.w = 115;
	toptrees.h = 33;

	//Trees for 30
	grasstree.x = 1417;
	grasstree.y = 367;
	grasstree.w = 408;
	grasstree.h = 224;

	//Final Grass
	onlygrass.x = 2092;
	onlygrass.y = 552;
	onlygrass.w = 97;
	onlygrass.h = 39;

	//Sky
	sky.x = 8;
	sky.y = 271;
	sky.w = 708;
	sky.h = 121;

	//Mountain
	mountain.x = 10;
	mountain.y = 71;
	mountain.w = 512;
	mountain.h = 131;

	//Bambu Tree
	bambu.x = 740;
	bambu.y = 293;
	bambu.w = 317;
	bambu.h = 98;

	//Bambu Tree Back
	bambuback.x = 572;
	bambuback.y = 105;
	bambuback.w = 320;
	bambuback.h = 97;

	//Lateral
	lateral.x = 5;
	lateral.y = 5;
	lateral.w = 1665;
	lateral.h = 704;
}

Background::~Background()
{}

// Load assets
bool Background::Start()
{
	LOG("Loading background assets");
	App->render->camera.x = 0;
	bool ret = true;
	movement = true;
	graphics = App->textures->Load("firstspritesheet.png");
	graphics1 = App->textures->Load("treespritesheet.png");
	graphics2 = App->textures->Load("fadespritesheet.png");
	end = App->textures->Load("secondfasespritesheet.png");
	laterals = App->textures->Load("Lateral.png");
	mid = App->textures->Load("mid_fade.png");
	mid1 = App->textures->Load("mid_fade.png");

	mus = App->audio->LoadMusic("08_Tall_cedar.ogg");

	Mix_PlayMusic(mus, -1);

	App->player->Enable();
	return ret;
}

// Load assets
bool Background::CleanUp()
{
	LOG("Unloading Background");
	movement = false;

	App->player->Disable();

	

	App->textures->Unload(graphics);
	App->textures->Unload(graphics1);
	App->textures->Unload(graphics2);
	App->textures->Unload(end);
	App->textures->Unload(laterals);
	App->textures->Unload(mid);
	App->textures->Unload(mid1);
	return true;
}

// Update: draw background
update_status Background::Update()
{
	// Draw everything --------------------------------------	
	int aux = -10, auxtree = -10, aux2 = 810, aux3 = 1775, aux4 = 780, aux5 = 2031, aux6 = 1390, aux7 = 5119, aux8 = 4690, aux9 = 6140, aux10 = 6630, aux11 = 7458;

	for (int i = 0; i < 6; i++) {
		App->render->Blit(graphics2, aux, 0, &trees, 0.55f);
		App->render->Blit(graphics2, aux + 42, 45, &toptree, 0.60f);
		App->render->Blit(graphics2, aux, 58, &backtrees, 0.60f);
		App->render->Blit(graphics2, aux + 170, 25, &toptrees, 0.60f);
		App->render->Blit(graphics2, auxtree, 82, &fisrttrees, 0.65f);

		aux += 320;
		auxtree += 319;
	}

	for (int i = 0; i < 15; i++) {
		App->render->Blit(graphics2, aux4, 193, &ground, 0.75f);
		aux4 += ground.w;
	}

	App->render->Blit(mid, 0, 0, &fademid, 0.00f);

	if (App->render->camera.x < -3800 && fade == true) {
		if (alpha_mid >= SDL_ALPHA_OPAQUE) {
			alpha_mid = 0;
			alpha_graph2 = 0;
			alpha_graph1 = 255;
			fade = false;
		}
		else {
			alpha_mid += 1.5;
		}
	}

	for (int i = 0; i < 18; i++) {
		App->render->Blit(graphics1, aux6, 0, &backfinal, 0.65f);
		aux6 += backfinal.w;
	}

	if (App->render->camera.x < -3800 && fade == false) {
		if (alpha_mid1 > SDL_ALPHA_TRANSPARENT) {
			App->render->Blit(mid1, 0, 0, &fademid, 0.00f);
			alpha_mid1 -= 1.5;
		}
		else {
			alpha_mid = 0;
		}

	}

	App->render->Blit(graphics, 1650, 0, &lonelytree, 0.73f);
	App->render->Blit(graphics, 1715, 0, &lonelytree, 0.69f);
	App->render->Blit(graphics, 1830, 0, &lonelytree, 0.71f);

	App->render->Blit(graphics, 2210, 0, &lonelytree, 0.71f);
	App->render->Blit(graphics, 1990, 0, &lonelytree, 0.72f);
	App->render->Blit(graphics, 2105, 0, &lonelytree, 0.73f);

	App->render->Blit(graphics, 2320, 0, &lonelytree, 0.73f);
	App->render->Blit(graphics, 2390, 0, &lonelytree, 0.71f);
	App->render->Blit(graphics, 2475, 0, &lonelytree, 0.72f);

	App->render->Blit(graphics, 0, 0, &groundandtrees, 0.75f);
	App->render->Blit(graphics, 1610, 185, &groundgrass, 0.75f);
	App->render->Blit(graphics, 115, 0, &Templesgate, 0.75f);
	App->render->Blit(graphics, 938, 132, &Temple, 0.75f);
	App->render->Blit(graphics, 1400, 92, &Temple2, 0.75f);

	for (int i = 0; i < 5; i++) {
		App->render->Blit(graphics, aux2, 203, &rockground, 0.75f);
		aux2 += rockground.w;
	}

	App->render->Blit(graphics, aux3, 0, &grasstrees2, 0.75f);

	for (int i = 0; i < 4; i++) {
		App->render->Blit(graphics, aux5, 0, &grasstrees4, 0.75f);
		aux5 += grasstrees4.w;
	}
	for (int i = 0; i < 22; i++) {
		App->render->Blit(graphics, aux7, grassy, &onlygrass, 0.75f);
		aux7 += onlygrass.w;
	}

	App->render->Blit(graphics, 4719, 0, &grasstree, 0.75f);

	if (currentTime > 89000) {
		alpha_end = 255;
		alpha_graph1 = 0;
	}

	for (int i = 0; i < 9; i++) {
		App->render->Blit(end, aux8, 0, &sky, 0.50f);
		aux8 += sky.w;
	}

	for (int i = 0; i < 11; i++) {
		App->render->Blit(end, aux9, SCREEN_HEIGHT - mountain.h, &mountain, 0.65f);
		aux9 += mountain.w;
	}

	for (int i = 0; i < 22; i++) {
		App->render->Blit(end, aux10, SCREEN_HEIGHT - bambuback.h, &bambuback, 0.70f);
		aux10 += bambuback.w;
	}

	for (int i = 0; i < 29; i++) {
		App->render->Blit(end, aux11, SCREEN_HEIGHT - bambu.h, &bambu, 0.75f);
		aux11 += bambu.w;
	}

	App->render->Blit(laterals, posx, posy, &lateral, 0.75f);

	//fader
	SDL_SetTextureAlphaMod(graphics2, alpha_graph2);
	SDL_SetTextureAlphaMod(graphics1, alpha_graph1);
	SDL_SetTextureAlphaMod(mid, alpha_mid);
	SDL_SetTextureAlphaMod(mid1, alpha_mid1);
	SDL_SetTextureAlphaMod(end, alpha_end);

	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->background, App->level2, 0.60f);
	}

	return UPDATE_CONTINUE;
}
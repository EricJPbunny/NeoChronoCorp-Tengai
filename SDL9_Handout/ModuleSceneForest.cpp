#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL_render.h"
#include "ModuleInput.h"
#include "ModuleSceneForest.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneForest::ModuleSceneForest()
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
	Templesgate.w = 87;
	Templesgate.h = 224;

	Templesgate2.x = 89;
	Templesgate2.y = 3;
	Templesgate2.w = 63;
	Templesgate2.h = 224;

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
	lateral.w = 1841;
	lateral.h = 704;
}

ModuleSceneForest::~ModuleSceneForest()
{}

// Load assets
bool ModuleSceneForest::Start()
{
	LOG("Loading background assets");
	alpha_graph1 = 0;
	bool ret = true;
	graphics = App->textures->Load("assets/sprite/firstspritesheet.png");
	graphics1 = App->textures->Load("assets/sprite/treespritesheet.png");
	graphics2 = App->textures->Load("assets/sprite/fadespritesheet.png");
	end = App->textures->Load("assets/sprite/secondfasespritesheet.png");
	laterals = App->textures->Load("assets/sprite/Lateral.png");
	mid = App->textures->Load("assets/sprite/mid_fade.png");
	mid1 = App->textures->Load("assets/sprite/mid_fade.png");

	mus = App->audio->LoadMusic("assets/audio/08_Tall_cedar.ogg");

	App->player->Enable();
	App->ui->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	coll_up =App->collision->AddCollider({ 0, 0, 99000, 0 }, COLLIDER_WALL);
	coll_down =App->collision->AddCollider({ 0,SCREEN_HEIGHT , 990000, 0 }, COLLIDER_WALL);
	coll_left = App->collision->AddCollider({ 0,0,0,SCREEN_HEIGHT }, COLLIDER_WALL);
	coll_right = App->collision->AddCollider({ SCREEN_WIDTH,0, 0,SCREEN_HEIGHT }, COLLIDER_WALL);

	//Enemies Ovni
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 830, 170);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 870, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 910, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::REDOVNI, 960, 80);

	//Enemies Ninja
	App->enemies->AddEnemy(ENEMY_TYPES::NINJA, 300, 0);

	App->audio->PlayMusic(mus);

	return ret;
}

// Load assets
bool ModuleSceneForest::CleanUp()
{
	LOG("Unloading Background");
	alpha_graph2 = 255;
	fade = true;

	App->render->camera.x = 0;

	App->audio->UnloadMusic(mus);

	App->collision->Disable();

	if (App->player2->IsEnabled()) {
		App->player2->Disable();
	}

	App->ui->Disable();
	App->player->Disable();
	App->enemies->Disable();

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
update_status ModuleSceneForest::Update()
{
	//Update Collision
	coll_left->SetPos(App->render->camera.x / SCREEN_SIZE, 0);
	coll_right->SetPos(SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE, 0);
	// Draw everything --------------------------------------	
	int aux = -10, auxtree = -10, aux2 = 810, aux3 = 1775, aux4 = 780, aux5 = 2031, aux6 = 1390, aux7 = 5119, aux8 = 4690, aux9 = 6140, aux10 = 6630, aux11 = 7880;

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

	if (App->render->camera.x > 5300 && fade == true) {
		if (alpha_mid >= SDL_ALPHA_OPAQUE) {
			alpha_mid = 0;
			alpha_graph2 = 0;
			alpha_graph1 = 255;
			fade = false;
		}
		else {
			alpha_mid += 0.10*speed;
		}
	}

	for (int i = 0; i < 18; i++) {
		App->render->Blit(graphics1, aux6, 0, &backfinal, 0.65f);
		aux6 += backfinal.w;
	}

	if (App->render->camera.x > 5300 && fade == false) {
		if (alpha_mid1 > SDL_ALPHA_TRANSPARENT) {
			App->render->Blit(mid1, 0, 0, &fademid, 0.00f);
			alpha_mid1 -= 0.10*speed;
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

	if (App->render->camera.x > 28780 && App->render->camera.x > -28880) {
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

	//Set Velocities
	if (App->player->IsEnabled() || App->player2->IsEnabled()) {
		App->ui->time = 9;
		App->ui->enemies_movement = true;
		if (App->render->camera.x < 1700) {
			speed = 9;
		}
		else if (App->render->camera.x > 1700 && App->render->camera.x < 5300) {
			speed = 6;
		}
		else if (App->render->camera.x > 5300 && App->render->camera.x < 8000) {
			speed = 12;
		}
		else if (App->render->camera.x > 8000 && App->render->camera.x < 10000) {
			speed -= 0.03;
		}
		else if (App->render->camera.x > 10000 && App->render->camera.x < 13100) {
			speed = 3;
		}
		else if (App->render->camera.x > 13100 && App->render->camera.x < 27340) {
			if (aux_time < 270)
			{
				speed = 0;
				aux_time++;
			}
			else
			{
				speed = 6;
			}

		}
		else if (App->render->camera.x > 27340 && App->render->camera.x < 30205) {
			posx -= 0.33*speed;
			posy += 0.21*speed;
			speed = 6;
		}
		else if (App->render->camera.x > 30205) {
			speed = 6;
		}

		if (App->render->camera.x > 26000 && App->render->camera.x < 27000) {
			grassy += 0.15*speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_TAB] == KEY_STATE::KEY_REPEAT) {
			speed = 24;
		}
	}
	//fader
	SDL_SetTextureAlphaMod(graphics2, alpha_graph2);
	SDL_SetTextureAlphaMod(graphics1, alpha_graph1);
	SDL_SetTextureAlphaMod(mid, alpha_mid);
	SDL_SetTextureAlphaMod(mid1, alpha_mid1);
	SDL_SetTextureAlphaMod(end, alpha_end);

	//Background Movement
	App->player2->position.x += speed / SCREEN_SIZE;
	App->player->position.x += speed/SCREEN_SIZE;
	App->render->camera.x += speed;

	//Blit To Screen

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN) {
		App->player->Enable();
	}

	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) {
		App->player2->Enable();
	}

	return UPDATE_CONTINUE;
}
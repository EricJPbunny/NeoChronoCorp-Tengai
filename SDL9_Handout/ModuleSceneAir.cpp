#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayer3.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL_render.h"
#include "ModuleInput.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneScore.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneAir::ModuleSceneAir()
{
	
}

ModuleSceneAir::~ModuleSceneAir()
{}

// Load assets
bool ModuleSceneAir::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("assets/sprite/sky_Background.png");
	graphics1= App->textures->Load("assets/sprite/spritesheet_ship.png");
	graphics2 = App->textures->Load("assets/sprite/destroyed_ship.png");
	//bacground starting rects

	MountainBg.x = 0;
	MountainBg.y = 192;
	MountainBg.h = 56;
	MountainBg.w =  959;

	SkyOne.x = 0;
	SkyOne.y = 0;
	SkyOne.h = 45;
	SkyOne.w = 959;

	SkyTwo.x = 0;
	SkyTwo.y = 79;
	SkyTwo.h = 45;
	SkyTwo.w = 959;

	SkyThree.x = 0;
	SkyThree.y = 124;
	SkyThree.h = 27;
	SkyThree.w = 959;

	SkyFour.x = 0;
	SkyFour.y = 151;
	SkyFour.h = 23;
	SkyFour.w = 959;

	FloorOne.x = 0;
	FloorOne.y = 281;
	FloorOne.h = 6;
	FloorOne.w = 959;

	FloorTwo.x = 0;
	FloorTwo.y = 287;
	FloorTwo.h = 8;
	FloorTwo.w = 959;

	FloorThree.x = 0;
	FloorThree.y = 295;
	FloorThree.h = 10;
	FloorThree.w = 959;

	FloorFour.x = 0;
	FloorFour.y = 305;
	FloorFour.h = 8;
	FloorFour.w = 959;

	FloorFive.x = 0;
	FloorFive.y = 313;
	FloorFive.h = 16;
	FloorFive.w = 959;


	BigSky.x = 0;
	BigSky.y = 455;
	BigSky.h = 391;
	BigSky.w = 160;


	exterior_ship.x = 0;
	exterior_ship.y = 0;
	exterior_ship.h = 222;
	exterior_ship.w = 271;

	destroyed_ship.x = 1;
	destroyed_ship.y = 1;
	destroyed_ship.h = 439;
	destroyed_ship.w = 629;


	//startup
	App->player2->Enable();
	App->ui->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	App->ui->score_koyori = 0;
	App->ui->score_sho = 0;

	App->audio->PlaySoundEffects(select_koyori);

	coll_up = App->collision->AddCollider({ 0, 0, 99000, 20 }, COLLIDER_WALL);
	coll_down = App->collision->AddCollider({ 0, SCREEN_HEIGHT - 4, 990000, 16 }, COLLIDER_WALL);
	coll_left = App->collision->AddCollider({ 0,0,0,SCREEN_HEIGHT }, COLLIDER_WALL);
	coll_right = App->collision->AddCollider({ SCREEN_WIDTH,0, 0,SCREEN_HEIGHT }, COLLIDER_WALL);

	App->audio->PlayMusic(mus);
	//Enemies

	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 480, 20,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 510, 112, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 540, 44, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 640, 64, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 690, 144, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 730, 0,2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 800, 164, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 820, 34, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 850, 0, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 890, 0, 2);


	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 920, 42,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 920, 87,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 920, 132,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 920, 177,1);


	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1020, 42,2);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1020, 87,2);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1020, 132,2);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1020, 177,2);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1150, 20, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1200, 44, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1270, 64, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1310, 144, 1);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1400, 66, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1480, 156, 1);
	

	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1970, 42, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1970, 87, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1970, 132, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1970, 177, 1);


	//Archers
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 1390, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 1460, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 1530, 160);
	


	// Ovnis

	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 420, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 440, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 460, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::REDOVNI, 480, 120);

	
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 700, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 720, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 740, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDOVNI, 760, 90);

	return ret;
}

// Load assets
bool ModuleSceneAir::CleanUp()
{
	LOG("Unloading Background");
	alpha_graph2 = 255;
	fade = true;

	App->render->camera.x = 0;

	App->audio->UnloadFx(select_sho);
	App->audio->UnloadFx(select_koyori);

	App->audio->UnloadMusic(mus);

	App->collision->Disable();

	if (App->player3->IsEnabled()) {
		App->player3->Disable();
	}

	App->ui->Disable();
	App->enemies->Disable();

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneAir::Update()
{
	//paint (pero el .net no)

	for (int i = 0; i < 5; ++i) 
	{
		App->render->Blit(graphics, (MountainBg.w * i) , 120, &MountainBg, bg_speed_default * 3);
		App->render->Blit(graphics, (SkyOne.w * i), 0, &SkyOne, bg_speed_default * 6);
		App->render->Blit(graphics, (SkyTwo.w * i), 45, &SkyTwo, bg_speed_default * 5);
		App->render->Blit(graphics, (SkyThree.w * i), 70, &SkyThree, bg_speed_default * 4);
		App->render->Blit(graphics, (SkyFour.w * i), 97, &SkyFour, bg_speed_default * 3);
		App->render->Blit(graphics, (FloorOne.w * i), 176, &FloorOne, bg_speed_default * 4);
		App->render->Blit(graphics, (FloorTwo.w * i), 182, &FloorTwo, bg_speed_default * 5);
		App->render->Blit(graphics, (FloorThree.w * i), 190, &FloorThree, bg_speed_default * 6);
		App->render->Blit(graphics, (FloorFour.w * i), 200, &FloorFour, bg_speed_default * 7);
		App->render->Blit(graphics, (FloorFive.w * i), 208, &FloorFive, bg_speed_default * 8);
		App->render->Blit(graphics, (BigSky.w * i), -391, &BigSky, bg_speed_default * 3);
	}

	//Y axis movement flags

	if (App->render->camera.x > 800) {
		speedy = -3;
	}

	//   SHIP & SHIP FLAGS
	if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN) {
		ship_flag1 = true;
		ship_flag2 = false;
		ship_flag3 = false;
		animspeed = 0;
	}
	if (ship_flag1) 
	{
		App->render->Blit(graphics1, 270,0,&exterior_ship, 0.00f, 0.00f);
		ship_flag2 = true;
	}
	if (ship_flag2)
	{
		ship_flag1 = false;
		if (animspeed <= 90) 
		{
			App->render->Blit(graphics1, 270 - animspeed, 0+ animspeed, &exterior_ship, 0.00f, 0.00f);
			animspeed++;
		}
		else 
		{
			if (animspeed < 220) {
				App->render->Blit(graphics1, 270 - animspeed, 90, &exterior_ship, 0.00f, 0.00f);
				animspeed++;
			}
			else {
				App->render->Blit(graphics1, 270  - 220, 90, &exterior_ship,0.00f,0.00f);
				ship_flag3 = true;
			}
		}
	}
	if (ship_flag3) 
	{
		ship_flag2 = false;
		App->render->Blit(graphics2, 270 - 232, 59, &destroyed_ship, 0.00f, 0.00f);
	}



	//Enable Players
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN) {
		if (!App->player2->IsEnabled()) {
			App->audio->PlaySoundEffects(select_sho);
			App->player2->Enable();
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN) {
		if (!App->player3->IsEnabled()) {
			App->audio->PlaySoundEffects(select_sho);
			App->player3->Enable();
		}
	}
	//Background Movement
	App->player2->position.x += speed / SCREEN_SIZE;
	App->player3->position.x += speed / SCREEN_SIZE;
	App->render->camera.x += speed;
	framerateset++;
	if (framerateset >= 2) {
		App->render->camera.y += speedy;
		App->player->position.y += speedy / SCREEN_SIZE;
		coll_down->SetPos(0, (App->render->camera.y / SCREEN_SIZE) + SCREEN_HEIGHT - 4);
		coll_up->SetPos(0, App->render->camera.y / SCREEN_SIZE);
		framerateset = 0;
	}
	//debuger
	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
		LOG("Breakpoint");
	}

	//Update Collision
	coll_left->SetPos(App->render->camera.x / SCREEN_SIZE, App->render->camera.y / SCREEN_SIZE);
	coll_right->SetPos((SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE),  App->render->camera.y / SCREEN_SIZE);
	//Debug Mode
	//Kill Koyori
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
		App->ui->num_life_koyori = 0;
		App->player->state = DEATH;
	}
	//Kill Sho
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
		App->ui->num_life_sho = 0;
	}
	
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) 
	{
		if (!god_mode)
		{
			if (App->player->IsEnabled()) {
				App->player->hitbox->SetPos(-100, -100);
			}
			if (App->player2->IsEnabled()) {
				App->player2->hitbox->SetPos(-100, -100);
			}
			if (App->player3->IsEnabled()) {
				App->player3->hitbox->SetPos(-100, -100);
			}
				god_mode = true;
		}
		else god_mode = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->audio->PlaySoundEffects(App->enemies->fx_death);
	}
	
	
	return UPDATE_CONTINUE;
}
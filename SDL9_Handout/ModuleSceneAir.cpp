#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneSelect.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayer3.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL_render.h"
#include "ModuleInput.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneScore.h"
#include "ModuleSceneStart.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneAir::ModuleSceneAir()
{
	current_animation_2 = NULL;

	//bacground starting rects

	MountainBg.x = 0;
	MountainBg.y = 192;
	MountainBg.h = 56;
	MountainBg.w = 959;

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
	destroyed_ship.w = 1643;

	BigSkyTwo.x = 582;
	BigSkyTwo.y = 910;
	BigSkyTwo.h = 114;
	BigSkyTwo.w = 320;

	BigSkyThree.x = 582;
	BigSkyThree.y = 686;
	BigSkyThree.h = 180;
	BigSkyThree.w = 319;

	BigSkyParalaxOne.x = 582;
	BigSkyParalaxOne.y = 882;
	BigSkyParalaxOne.h = 28;
	BigSkyParalaxOne.w = 320;

	BigSkyParalaxTwo.x = 582;
	BigSkyParalaxTwo.y = 866;
	BigSkyParalaxTwo.h = 16;
	BigSkyParalaxTwo.w = 320;

	FloorFour.x = 0;
	FloorFour.y = 305;
	FloorFour.h = 8;
	FloorFour.w = 959;

	FloorFive.x = 0;
	FloorFive.y = 313;
	FloorFive.h = 16;
	FloorFive.w = 959;

	inside_2.x = 178;
	inside_2.y = 236;
	inside_2.h = 224;
	inside_2.w = 57;

	grid.x = 3;
	grid.y = 236;
	grid.h = 224;
	grid.w = 153;

	peak.x = 0;
	peak.y = 376;
	peak.h = 16;
	peak.w = 254;

	peak2.x = 0;
	peak2.y = 350;
	peak2.h = 24;
	peak2.w = 256;

	peak3.x = 0;
	peak3.y = 332;
	peak3.h = 16;
	peak3.w = 237;

	big_cloud.x = 1;
	big_cloud.y = 397;
	big_cloud.h = 29;
	big_cloud.w = 188;

	cloud.x = 1;
	cloud.y = 403;
	cloud.h = 16;
	cloud.w = 38;

	cloud2.x = 49;
	cloud2.y = 401;
	cloud2.h = 20;
	cloud2.w = 58;

	cloud3.x = 118;
	cloud3.y = 403;
	cloud3.h = 15;
	cloud3.w = 42;

	cloud4.x = 170;
	cloud4.y = 400;
	cloud4.h = 29;
	cloud4.w = 53;

	fog.x = 252;
	fog.y = 431;
	fog.h = 15;
	fog.w = 128;

	fog2.x = 113;
	fog2.y = 434;
	fog2.h = 12;
	fog2.w = 128;

	group_cloud.x = 280;
	group_cloud.y = 340;
	group_cloud.h = 50;
	group_cloud.w = 302;

	cloud_inter.x = 183;
	cloud_inter.y = 467;
	cloud_inter.h = 42;
	cloud_inter.w = 70;

	cloud_inter2.x = 174;
	cloud_inter2.y = 519;
	cloud_inter2.h = 79;
	cloud_inter2.w = 112;

	cloud_inter3.x = 177;
	cloud_inter3.y = 609;
	cloud_inter3.h = 71;
	cloud_inter3.w = 102;

	lion.x = 25;
	lion.y = 488;
	lion.h = 185;
	lion.w = 144;

	//Animation
	inside.PushBack({ 2,1,304,224 });
	inside.PushBack({ 317,1,304,224 });
	inside.PushBack({ 635,1,304,224 });
	inside.speed = 0.30f;

	piston.PushBack({ 273,325,98,119 });
	piston.PushBack({ 389,325,98,119 });
	piston.PushBack({ 510,325,98,119 });
	piston.PushBack({ 630,325,98,119 });
	piston.PushBack({ 748,323,98,119 });
	piston.speed = 0.35f;

	screw.PushBack({ 273,236,48,73 });
	screw.PushBack({ 338,236,48,73 });
	screw.PushBack({ 402,236,48,73 });
	screw.PushBack({ 470,237,48,73 });
	screw.PushBack({ 539,237,48,73 });
	screw.speed = 0.30f;

	
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
	graphics3 = App->textures->Load("assets/sprite/inside_ship_SS.png");


	//startup
	//1Player vs 2Player
	if (App->scene_select->one_player) {
		if (App->scene_select->sho_p1) {
			App->player2->Enable();
		}
		else {
			App->player3->Enable();
		}
	}
	else {
		App->player2->Enable();
		App->player3->Enable();
	}

	App->ui->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	App->ui->score_junis = 0;
	App->ui->score_sho = 0;
	App->scene_select->time_num = 9;

	coll_up = App->collision->AddCollider({ 0, 0, 99000, 20 }, COLLIDER_WALL);
	coll_down = App->collision->AddCollider({ 0, SCREEN_HEIGHT - 4, 990000, 16 }, COLLIDER_WALL);
	coll_left = App->collision->AddCollider({ 0,0,0,SCREEN_HEIGHT }, COLLIDER_WALL);
	coll_right = App->collision->AddCollider({ SCREEN_WIDTH,0, 0,SCREEN_HEIGHT }, COLLIDER_WALL);

	mus = App->audio->LoadMusic("assets/audio/06_Torn_silence.ogg");
	select_sho = App->audio->LoadEffect("assets/audio/select_sho.wav");
	select_junis = App->audio->LoadEffect("assets/audio/select_junis.wav");

	App->audio->PlayMusic(mus);
	//Enemies
	App->enemies->AddEnemy(ENEMY_TYPES::ULTI, 200, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 380, 20,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 410, 112, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 440, 44, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 470, 64, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 510, 144, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 550, 0,2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 600, 164, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 620, 34, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 650, 0, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 690, 0, 2);
	//App->enemies->AddEnemy(ENEMY_TYPES::BOSSHEAD, 3500, -650, 2);
	//App->enemies->AddEnemy(ENEMY_TYPES::BUDA, 4450, -760, 2);
	//App->enemies->AddEnemy(ENEMY_TYPES::TURRET, 4450, -628, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::ELF, 90, 60, 2);


	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 690, 42,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 690, 87,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 690, 132,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 690, 177,1);


	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 770, 42,2);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 770, 87,2);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 770, 132,2);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 770, 177,2);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 910, 20, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 940, 44, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 970, 64, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1010, 144, 1);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1120, 66, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1170, 156, 1);
	

	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1970, 42, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1970, 87, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1970, 132, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1970, 177, 1);


	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1370, (App->render->camera.y / SCREEN_SIZE) - 70, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1370, (App->render->camera.y / SCREEN_SIZE) - 30, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1370, (App->render->camera.y / SCREEN_SIZE) + 10, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 1370, (App->render->camera.y / SCREEN_SIZE) + 50, 3);

	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1720, (App->render->camera.y / SCREEN_SIZE) -200, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1810, (App->render->camera.y / SCREEN_SIZE) - 180, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1840, (App->render->camera.y / SCREEN_SIZE) - 180, 3);

	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1870, (App->render->camera.y / SCREEN_SIZE) - 300, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1910, (App->render->camera.y / SCREEN_SIZE) - 300, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1950, (App->render->camera.y / SCREEN_SIZE) - 300, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 1990, (App->render->camera.y / SCREEN_SIZE) - 300, 4);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2050, (App->render->camera.y / SCREEN_SIZE) - 500, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2080, (App->render->camera.y / SCREEN_SIZE) - 500, 2);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2150, (App->render->camera.y / SCREEN_SIZE) - 500, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2180, (App->render->camera.y / SCREEN_SIZE) - 500, 2);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2190, (App->render->camera.y / SCREEN_SIZE) -500, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2230, (App->render->camera.y / SCREEN_SIZE) -500, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2300, (App->render->camera.y / SCREEN_SIZE) - 450, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2320, (App->render->camera.y / SCREEN_SIZE) - 400, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2390, (App->render->camera.y / SCREEN_SIZE) - 500, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2300, (App->render->camera.y / SCREEN_SIZE) - 650, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2320, (App->render->camera.y / SCREEN_SIZE) - 600, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2390, (App->render->camera.y / SCREEN_SIZE) - 300, 3);
	

	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2400, (App->render->camera.y / SCREEN_SIZE) - 650, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2420, (App->render->camera.y / SCREEN_SIZE) - 600, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2430, (App->render->camera.y / SCREEN_SIZE) - 520, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2470, (App->render->camera.y / SCREEN_SIZE) - 500, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2490, (App->render->camera.y / SCREEN_SIZE) - 520, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2490, (App->render->camera.y / SCREEN_SIZE) - 300, 3);



	//Archers
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 1030, 60, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 1070, 110, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 1110, 160, 1);
	
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 2100, (App->render->camera.y / SCREEN_SIZE) - 400, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 2250, (App->render->camera.y / SCREEN_SIZE) - 450, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 2350, (App->render->camera.y / SCREEN_SIZE) - 450, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 2700, (App->render->camera.y / SCREEN_SIZE) + 60, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 2850, (App->render->camera.y / SCREEN_SIZE) + 150, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 2950, (App->render->camera.y / SCREEN_SIZE) + 120, 1);

	

	// Ovnis

	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 320, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 340, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 360, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::REDOVNI, 380, 120);

	
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 500, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 520, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 540, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDOVNI, 560, 90);

	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 2900, -700);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 2930, -650);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENOVNI, 2960, -600);
	App->enemies->AddEnemy(ENEMY_TYPES::REDOVNI, 2930, -550);

	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 3070, -570, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 3070, -610, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 3070, -650, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 3070, -690, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 3030, -700, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 3030, -630, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::ARCHER, 3030, -560, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3000, -700, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 2980, -560, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3030, -600, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3010, -650, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3000, -640, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3100, -640, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3200, -700, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3280, -560, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3230, -600, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3210, -650, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 3200, -640, 1);


	//Final
	
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4380, -620,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4410, -712,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4440, -644,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4470, -764,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4510, -744,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4550, -600,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4600, -764,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4620, -634,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4650, -700,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4690, -700,1);



	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 4690, -642,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 4690, -687,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 4690, -732,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 4690, -777,1);


	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 4770, -642,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 4770, -687,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 4770, -732,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 4770, -777,1);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4910, -620,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4940, -644,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 4970, -664,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 5010, -744,1);


	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 5120, -666,1);
	App->enemies->AddEnemy(ENEMY_TYPES::KNIFE, 5170, -756,1);


	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 5970, -642,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 5970, -687,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 5970, -732,1);
	App->enemies->AddEnemy(ENEMY_TYPES::BIRD, 5970, -777,1);

	return ret;
}

// Load assets
bool ModuleSceneAir::CleanUp()
{
	LOG("Unloading Background");
	alpha_graph2 = 255;
	fade = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->audio->UnloadFx(select_junis);
	App->audio->UnloadFx(select_sho);
	App->audio->UnloadFx(select_koyori);

	App->audio->UnloadMusic(mus);

	App->collision->Disable();

	if (App->player2->IsEnabled()) {
		App->player2->Disable();
	}

	if (App->player3->IsEnabled()) {
		App->player3->Disable();
	}

	App->ui->Disable();
	App->enemies->Disable();

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->textures->Unload(graphics3);

	return true;
}

// Update: draw background
update_status ModuleSceneAir::Update()
{
	if (App->player2->IsEnabled() || App->player3->IsEnabled()) {
		speed = 3;

		//Y axis movement flags
		if (App->render->camera.x > 2500) {
			speedy = -3;
		}
		if (App->render->camera.y < -2187) {
			speedy = 0;
		}
	}
	
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
		App->render->Blit(graphics, (peak.w * i), 192, &peak, bg_speed_default * 8);
		App->render->Blit(graphics, (peak2.w * i), 176, &peak2, bg_speed_default * 7);
		App->render->Blit(graphics, (peak3.w * i), 174, &peak3, bg_speed_default * 6);
		App->render->Blit(graphics, (peak3.w * i), 166, &peak3, bg_speed_default * 5);
	}

	for (int i = 0; i < 20; ++i) {
		App->render->Blit(graphics, (BigSky.w * i)-35, -391, &BigSky, bg_speed_default * 3);
		App->render->Blit(graphics, (BigSkyTwo.w * i), -505, &BigSkyTwo, bg_speed_default * 3);
		App->render->Blit(graphics, (BigSkyParalaxTwo.w * i), -549, &BigSkyParalaxTwo, bg_speed_default * 2);
		App->render->Blit(graphics, (BigSkyParalaxOne.w * i), -533, &BigSkyParalaxOne, bg_speed_default * 3);
		App->render->Blit(graphics, (big_cloud.w * i), -520, &big_cloud, bg_speed_default * 3);
		App->render->Blit(graphics, (BigSkyThree.w * i), -729, &BigSkyThree, 0);
	
	}
	for (int i = 0; i < 40; ++i) {
		App->render->Blit(graphics, (fog2.w * i), -561, &fog2, bg_speed_default * 2);
		App->render->Blit(graphics, (fog.w * i) + 3, -543, &fog, bg_speed_default * 3);
		App->render->Blit(graphics, (group_cloud.w * i), -600, &group_cloud, bg_speed_default * 5);
	}

	//   SHIP & SHIP FLAGS
	if (App->render->camera.x>9400 && App->render->camera.x<9700) {
		ship_flag1 = true;
		ship_flag2 = false;
		ship_flag3 = false;
		animspeed = 0;
	}
	if (ship_flag1) 
	{
		if (timer) {
			time_on_entry = SDL_GetTicks();
			timer = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		App->render->Blit(graphics1, 270, 0, &exterior_ship, 0.00f, 0.00f);
		if (current_time > 16000) {
			ship_flag2 = true;
		}
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
				App->render->Blit(graphics1, 50, 90, &exterior_ship,0.00f,0.00f);
				if (timer) {
					time_on_entry = SDL_GetTicks();
					timer = false;
				}
				current_time = SDL_GetTicks() - time_on_entry;
				if (current_time > 32000) {
					ship_flag3 = true;
				}
			}
		}
	}
	if (ship_flag3) 
	{
		ship_flag2 = false;
		App->render->Blit(graphics2, 270 - 232-animspeed, 59, &destroyed_ship, 0.00f, 0.00f);
		animspeed++;
		if (animspeed > 190) 
		{
			ship_flag4 = true;
			ship_flag3 = false;
			animspeed = 0;
		}
	}
	if (ship_flag4) 
	{
		if (animspeed < 274) {
			App->render->Blit(graphics2, -152 , 59 - animspeed, &destroyed_ship, 0.00f, 0.00f);
			animspeed++;
			ship_flag5 = true;
			current_animation = &piston;
			SDL_Rect r_3 = current_animation->GetCurrentFrame();
			App->render->Blit(graphics3, (App->render->camera.x / SCREEN_SIZE) +87 , (App->render->camera.y / SCREEN_SIZE) +316-animspeed, &r_3);
			App->render->Blit(graphics3, (App->render->camera.x / SCREEN_SIZE) -30, (App->render->camera.y / SCREEN_SIZE) + 316 - animspeed, &r_3);
			App->render->Blit(graphics3, (App->render->camera.x / SCREEN_SIZE) + 198, (App->render->camera.y / SCREEN_SIZE) + 316 - animspeed, &r_3);
		}
		else {
			if (ship_flag5) {
					if (animspeed < 2500) {
						LOG("No mames");
						if (App->render->camera.x<21500) {
							speed_screw = 0.5f;
							current_animation_2 = &inside;
							SDL_Rect r = current_animation_2->GetCurrentFrame();
							App->render->Blit(graphics3, (App->render->camera.x / SCREEN_SIZE + speed_screw) + 57, App->render->camera.y / SCREEN_SIZE, &r);
							App->render->Blit(graphics3, 0, 0, &inside_2, 0.00f, 0.00f);
						}
						
						App->render->Blit(graphics2, +115-animspeed , -215, &destroyed_ship, 0.00f, 0.00f);
						App->render->Blit(graphics3, 1126 - animspeed, 20, &lion, speed_lion, 0.00f);
						App->render->Blit(graphics3, 1126-animspeed, 0, &grid, 0.00f, 0.00f);
						
						if (App->render->camera.x > 17500 && App->render->camera.x < 20500) {
							animspeed = 790;
						}

						//screw
						current_animation_3 = &screw;
						SDL_Rect r_2 = current_animation_3->GetCurrentFrame();
						App->render->Blit(graphics3, (App->render->camera.x / SCREEN_SIZE ) + 702-animspeed, (App->render->camera.y / SCREEN_SIZE)+150, &r_2);
						
						//piston
						current_animation = &piston;
						SDL_Rect r_3 = current_animation->GetCurrentFrame();
						App->render->Blit(graphics3, (App->render->camera.x / SCREEN_SIZE) + 345-animspeed, (App->render->camera.y / SCREEN_SIZE) + 42, &r_3);
						App->render->Blit(graphics3, (App->render->camera.x / SCREEN_SIZE) + 464-animspeed, (App->render->camera.y / SCREEN_SIZE) + 42 , &r_3);
						App->render->Blit(graphics3, (App->render->camera.x / SCREEN_SIZE) + 578-animspeed, (App->render->camera.y / SCREEN_SIZE) + 42, &r_3);

						animspeed++;
					}
			}
		}
	}


	//Enable Players
	if (App->scene_start->credit_num > 0) {
		if (App->scene_select->sho_p1) {
			if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || App->input->controller_START_button == KEY_STATE::KEY_DOWN) {
				if (!App->player2->IsEnabled()) {
					App->audio->PlaySoundEffects(select_sho);
					App->player2->Enable();
					App->scene_start->credit_num--;
					App->ui->time = 9;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN || App->input->controller_START_button2 == KEY_STATE::KEY_DOWN) {
				if (!App->player3->IsEnabled()) {
					App->audio->PlaySoundEffects(select_junis);
					App->player3->Enable();
					App->scene_start->credit_num--;
					App->ui->time = 9;
				}
			}
		}
		else {
			if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN || App->input->controller_START_button2 == KEY_STATE::KEY_DOWN) {
				if (!App->player2->IsEnabled()) {
					App->audio->PlaySoundEffects(select_sho);
					App->player2->Enable();
					App->scene_start->credit_num--;
					App->ui->time = 9;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || App->input->controller_START_button == KEY_STATE::KEY_DOWN) {
				if (!App->player3->IsEnabled()) {
					App->audio->PlaySoundEffects(select_junis);
					App->player3->Enable();
					App->scene_start->credit_num--;
					App->ui->time = 9;
				}
			}
		}
	}

	

	//teleport
	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN) {
		App->render->camera.x = 8000;
		App->render->camera.y = -2000;
	}

	//Background Movement
	App->player2->position.x += speed / SCREEN_SIZE;
	App->player3->position.x += speed / SCREEN_SIZE;
	App->render->camera.x += speed;
	framerateset++;
	if (framerateset >= 2) {
		App->render->camera.y += speedy;
		App->player2->position.y += speedy / SCREEN_SIZE;
		App->player3->position.y += speedy / SCREEN_SIZE;
		coll_down->SetPos(0, (App->render->camera.y / SCREEN_SIZE) + SCREEN_HEIGHT - 4);
		coll_up->SetPos(0, App->render->camera.y / SCREEN_SIZE);
		framerateset = 0;
	}
	//debuger
	

	//Update Collision
	coll_left->SetPos(App->render->camera.x / SCREEN_SIZE, App->render->camera.y / SCREEN_SIZE);
	coll_right->SetPos((SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE),  App->render->camera.y / SCREEN_SIZE);
	//Debug Mode
	//Kill Koyori
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
		if (App->player3->IsEnabled()) {
			App->ui->num_life_junis = 0;
		}
	}
	//Kill Sho
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
		if (App->player2->IsEnabled()) {
			App->ui->num_life_sho = 0;
		}
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

	if (App->input->keyboard[SDL_SCANCODE_F8]==KEY_STATE::KEY_DOWN || App->render->camera.x>30000 || App->ui->time == 0) {
		App->ui->time == 9;
		App->fade->FadeToBlack(App->scene_air, App->scene_score, 0.90f);
	}
	
	return UPDATE_CONTINUE;
}
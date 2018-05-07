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


	//startup
	App->player->Enable();
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

	if (App->player2->IsEnabled()) {
		App->player2->Disable();
	}

	App->ui->Disable();
	App->player->Disable();
	App->enemies->Disable();

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneAir::Update()
{
	//paint (pero el .net no)

	App->render->Blit(graphics, 0, 120, &MountainBg, 0.20f);
	App->render->Blit(graphics, 0, 0, &SkyOne, 0.30f);
	App->render->Blit(graphics, 0, 45, &SkyTwo, 0.25f);
	App->render->Blit(graphics, 0, 70, &SkyThree, 0.20f);
	App->render->Blit(graphics, 0, 97, &SkyFour, 0.15f);
	App->render->Blit(graphics, 0, 176, &FloorOne, 0.20f);
	App->render->Blit(graphics, 0, 182, &FloorTwo, 0.30f);
	App->render->Blit(graphics, 0, 190, &FloorThree, 0.40f);
	App->render->Blit(graphics, 0, 200, &FloorFour, 0.50f);
	App->render->Blit(graphics, 0, 208, &FloorFive, 0.60f);

	//Enable Players
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN) {
		if (!App->player->IsEnabled()) {
			App->audio->PlaySoundEffects(select_koyori);
			App->player->Enable();
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN) {
		if (!App->player2->IsEnabled()) {
			App->audio->PlaySoundEffects(select_sho);
			App->player2->Enable();
		}
	}
	//Background Movement
	App->player2->position.x += speed / SCREEN_SIZE;
	App->player->position.x += speed / SCREEN_SIZE;
	App->render->camera.x += speed;

	//Update Collision
	coll_left->SetPos(App->render->camera.x / SCREEN_SIZE, 0);
	coll_right->SetPos((SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE), 0);
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
			App->player->hitbox->SetPos(-100, -100);
			if (App->player2->IsEnabled())
			App->player2->hitbox->SetPos(-100, -100);
			god_mode = true;
		}
		else god_mode = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->audio->PlaySoundEffects(App->enemies->fx_death);
	}
	
	
	return UPDATE_CONTINUE;
}
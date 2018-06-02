#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleSceneScore.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneStart.h"
#include "ModuleSceneSelect.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayer3.h"
#include "ModulePartner.h"
#include "ModulePartner2.h"
#include "ModulePartner3.h"
#include "ModuleUlti2.h"
#include "ModuleUlti3.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"
#include "ModuleFonts.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = scene_intro = new ModuleSceneIntro();
	modules[i++] = scene_start = new ModuleSceneStart();
	modules[i++] = scene_select = new ModuleSceneSelect();
	modules[i++] = scene_air = new ModuleSceneAir();
	modules[i++] = scene_score = new ModuleScore();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = pu = new ModulePowerup();
	modules[i++] = partner3 = new ModulePartner3();
	modules[i++] = partner2 = new ModulePartner2();
	modules[i++] = partner = new ModulePartner();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = player2 = new ModulePlayerTwo();
	modules[i++] = player3 = new ModulePlayer3();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = ulti2 = new ModuleUlti2();
	modules[i++] = ulti3 = new ModuleUlti3();
	modules[i++] = ui = new ModuleUI();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fade = new ModuleFadeToBlack();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Deactivate modules here ----
	App->ui->Disable();
	scene_score->Disable();
	scene_start->Disable();
	scene_select->Disable();
	scene_air->Disable();
	player->Disable();
	player2->Disable();
	ulti2->Disable();
	ulti3->Disable();
	player3->Disable();
	partner3->Disable();
	collision->Disable();
	enemies->Disable();
	// ----------------------------

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
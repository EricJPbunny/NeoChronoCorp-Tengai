#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// Background / sky
	ground.x = 15;
	ground.y = 367;
	ground.w = 810;
	ground.h = 224;

	Templesgate.x = 2;
	Templesgate.y = 3;
	Templesgate.w = 150;
	Templesgate.h = 224;

	backtrees.x = 1221;
	backtrees.y = 2;
	backtrees.w = 320;
	backtrees.h = 136;

	fisrttrees.x = 154;
	fisrttrees.y = 2;
	fisrttrees.w = 319;
	fisrttrees.h = 64;

	rockground.x = 828;
	rockground.y = 570;
	rockground.w = 160;
	rockground.h = 21;
	
	trees.x = 1495;
	trees.y = 140;
	trees.w = 320;
	trees.h = 224;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Background_spritesheet.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	int aux = 0, aux2 = 810, aux3 = 0;
	for (int i = 0; i < 2; i++) 
	{
		App->render->Blit(graphics, aux, 0, &trees, 0.60f);
		aux += 320;
	}
	for (int i = 0; i < 3; i++) 
	{
		App->render->Blit(graphics, aux3, 56, &backtrees, 0.65f);
		App->render->Blit(graphics, aux3, 80, &fisrttrees, 0.70f);
		aux3 += 320;
	}
	App->render->Blit(graphics, 0, 0, &ground, 0.75f);
	App->render->Blit(graphics, 115, 0, &Templesgate, 0.75f);
	for (int i = 0; i < 5; i++) 
	{
		App->render->Blit(graphics, aux2, 203, &rockground, 0.75f);
		aux2 += 160;
	}

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	
	

	return UPDATE_CONTINUE;
}
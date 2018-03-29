#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// Background / sky
	groundandtrees.x = 15;
	groundandtrees.y = 367;
	groundandtrees.w = 810;
	groundandtrees.h = 224;

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

	ground.x = 510;
	ground.y = 210;
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

	Temple.x = 22;
	Temple.y = 232;
	Temple.w = 348;
	Temple.h = 61;

	Temple2.x = 153;
	Temple2.y = 109;
	Temple2.w = 155;
	Temple2.h = 109;

	lonelytree.x = 384;
	lonelytree.y = 85;
	lonelytree.w = 25;
	lonelytree.h = 280;

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
	int aux = 0, aux2 = 810, aux3 = 1775, aux4 = 780, aux5 = 2031;
	for (int i = 0; i < 5; i++) {
		App->render->Blit(graphics, aux, 0, &trees, 0.55f);
		App->render->Blit(graphics, aux, 58, &backtrees, 0.60f);
		App->render->Blit(graphics, aux, 82, &fisrttrees, 0.65f);
		aux += 320;
	}
	/*for (int i = 0; i < 5; i++) {
	App->render->Blit(graphics, aux3, 58, &backtrees, 0.65f);
	App->render->Blit(graphics, aux3, 82, &fisrttrees, 0.70f);
	aux3 += 320;
	}*/
	for (int i = 0; i < 15; i++) {
		App->render->Blit(graphics, aux4, 193, &ground, 0.75f);
		aux4 += 64;
	}
	App->render->Blit(graphics, 0, 0, &groundandtrees, 0.75f);
	App->render->Blit(graphics, 1610, 185, &groundgrass, 0.75f);
	App->render->Blit(graphics, 115, 0, &Templesgate, 0.75f);
	App->render->Blit(graphics, 938, 132, &Temple, 0.75f);
	App->render->Blit(graphics, 1400, 92, &Temple2, 0.75f);
	for (int i = 0; i < 5; i++) {
		App->render->Blit(graphics, aux2, 203, &rockground, 0.75f);
		aux2 += 160;
	}
	App->render->Blit(graphics, aux3, 0, &grasstrees2, 0.75f);
	for (int i = 0; i<5; i++) {
		App->render->Blit(graphics, aux5, 0, &grasstrees4, 0.75f);

		aux5 += 672;
	}
		
		
		
	
	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	// TODO 3: Animate the girl on the ship (see the sprite sheet)



	return UPDATE_CONTINUE;
}
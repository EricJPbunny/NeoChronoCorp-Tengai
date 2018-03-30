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


	//Temple llarg
	Temple.x = 22;
	Temple.y = 232;
	Temple.w = 348;
	Temple.h = 61;

	//Temple gran
	Temple2.x = 153;
	Temple2.y = 109;
	Temple2.w = 155;
	Temple2.h = 109;

	//Arbre sorlitari que es va repetint el mateix
	lonelytree.x = 384;
	lonelytree.y = 85;
	lonelytree.w = 25;
	lonelytree.h = 280;

	//Provaconjunta darbres solitaris
	/*lonelytree1.x = 1874;
	lonelytree1.y = 24;
	lonelytree1.w = 912;
	lonelytree1.h = 208;*/

	//Backgrond abans del scroll en diagonal
	backfinal.x = 826;
	backfinal.y = 140;
	backfinal.w = 320;
	backfinal.h = 224;

	//La punta d'un arbre
	toptree.x = 478;
	toptree.y = 52;
	toptree.w = 15;
	toptree.h = 14;


	//Les tres puntes dels arbres
	toptrees.x = 154;
	toptrees.y = 68;
	toptrees.w = 115;
	toptrees.h = 33;

	//Arbres per fer els 30
	grasstree.x = 1417;
	grasstree.y = 367;
	grasstree.w = 408;
	grasstree.h = 224;

	//Gespa del final
	onlygrass.x = 2092;
	onlygrass.y = 552;
	onlygrass.w = 97;
	onlygrass.h = 39;
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
	int aux = 0, aux2 = 810, aux3 = 1775, aux4 = 780, aux5 = 2031, aux6=2350, aux7= 5119;
	for (int i = 0; i < 5; i++) {
		App->render->Blit(graphics, aux, 0, &trees, 0.55f);
		App->render->Blit(graphics, aux + 42, 45, &toptree, 0.60f);
		App->render->Blit(graphics, aux, 58, &backtrees, 0.60f);
		App->render->Blit(graphics, aux +170, 25, &toptrees, 0.60f);
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
	App->render->Blit(graphics, 1650, 0, &lonelytree, 0.73f);
	App->render->Blit(graphics, 1810, 0, &lonelytree, 0.73f);
	App->render->Blit(graphics, 1870, 0, &lonelytree, 0.73f);

	App->render->Blit(graphics, 1910, 0, &lonelytree, 0.73f);
	App->render->Blit(graphics, 1990, 0, &lonelytree, 0.73f);
	App->render->Blit(graphics, 2100, 0, &lonelytree, 0.73f);

	App->render->Blit(graphics, 2220, 0, &lonelytree, 0.73f);
	App->render->Blit(graphics, 2500, 0, &lonelytree, 0.73f);
	App->render->Blit(graphics, 2400, 0, &lonelytree, 0.73f);
	
	/*App->render->Blit(graphics, 1650, 0, &lonelytree, 0.73f);*/

	App->render->Blit(graphics, 0, 0, &groundandtrees, 0.75f);
	App->render->Blit(graphics, 1610, 185, &groundgrass, 0.75f);
	App->render->Blit(graphics, 115, 0, &Templesgate, 0.75f);
	App->render->Blit(graphics, 938, 132, &Temple, 0.75f);
	App->render->Blit(graphics, 1400, 92, &Temple2, 0.75f);

	for (int i = 0; i < 10; i++) {
		App->render->Blit(graphics, aux6, 0, &backfinal, 0.65f);
		aux6 += 320;
	}
	
	for (int i = 0; i < 5; i++) {
		App->render->Blit(graphics, aux2, 203, &rockground, 0.75f);
		aux2 += 160;
	}
	App->render->Blit(graphics, aux3, 0, &grasstrees2, 0.75f);
	for (int i = 0; i < 4; i++) {
		App->render->Blit(graphics, aux5, 0, &grasstrees4, 0.75f);
		aux5 += 672;
	}
	for (int i = 0; i < 12; i++) {
		App->render->Blit(graphics, aux7, 185, &onlygrass, 0.75f);
		aux7 += 97;
	}
	
	App->render->Blit(graphics, 4719, 0, &grasstree, 0.75f);
		
	
	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	// TODO 3: Animate the girl on the ship (see the sprite sheet)



	return UPDATE_CONTINUE;
}
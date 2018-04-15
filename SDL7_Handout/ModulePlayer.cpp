#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneForest.h"


ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 68, 53, 32, 28 });
	idle.PushBack({ 108, 54, 32, 27 });
	idle.PushBack({ 148, 54, 32, 27 });
	idle.speed = 0.20f;

	// walk backward animation (arcade sprite sheet)
	backward.PushBack({ 192, 53, 27, 29 });
	backward.PushBack({ 232, 54, 28, 28 });
	backward.PushBack({ 272, 54, 27, 28 });
	backward.speed = 0.15f;

	//Intermediate
	intermediate.PushBack({ 187,95,27,29 });
	intermediate.PushBack({ 230,95,24,28 });
	intermediate.PushBack({ 270,95,26,29 });
	intermediate.speed = 0.05f;

	//Intermediate return
	intermediatereturn.PushBack({ 270,95,26,29 });
	intermediatereturn.PushBack({ 230,95,24,28 });
	intermediatereturn.PushBack({ 187,95,27,29 });
	intermediatereturn.speed = 0.05f;

	//Walk
	walk.PushBack({ 74,12,27,27 });
	walk.PushBack({ 114,13,27,27 });
	walk.PushBack({ 153,11,27,29 });
	walk.PushBack({ 194,8,27,31 });
	walk.PushBack({ 234,9,27,26 });
	walk.PushBack({ 274,12,28,28 });
	walk.PushBack({ 313,15,30,25 });
	walk.speed = 0.2f;

	//Spin
	spin.PushBack({ 22,95,33,29 });
	spin.PushBack({ 62,95,26,29 });
	spin.PushBack({ 102,95,30,29 });
	spin.PushBack({ 142,95,28,29 });
	spin.speed = 0.15f;

	//Spin Circle
	spin_circle.PushBack({ 211, 161, 32, 32 });
	spin_circle.PushBack({ 248,161,32,32 });
	spin_circle.PushBack({ 289,161,32,32 });
	spin_circle.PushBack({ 322,161,32,32 });
	spin_circle.PushBack({ 355,161,32,32 });
	spin_circle.PushBack({ 389,161,32,32 });
	spin_circle.PushBack({ 423,161,32,32 });
	spin_circle.PushBack({ 457,161,32,32 });
	spin_circle.PushBack({ 356,196,32,32 });
	spin_circle.speed = 0.40;

	//Death
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 2,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 143,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 143,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 300,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 2,292, 130, 130 });
	death_circle.speed = 0.8;

	//Death Player
	death.x = 308;
	death.y = 54;
	death.w = 30;
	death.h = 25;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/sprite/miko.png"); // arcade version
	player_death = App->textures->Load("assets/sprite/Death_Player.png");
	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player");
	App->textures->Unload(graphics);
	App->textures->Unload(player_death);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	float speed = 2.5;

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (aux < 30) {
			current_animation = &intermediate;
			aux++;
		}
		else if (current_animation != &backward)
		{
			backward.Reset();
			current_animation = &backward;
		}
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) {
		aux = 0;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
		if (position.y == SCREEN_HEIGHT) {
			current_animation = &walk;
		}
		else {
			current_animation = &idle;
		}
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
		if (aux < 30) {
			current_animation = &intermediate;
			aux++;
		}
		else {
			current_animation = &backward;
		}
		position.y -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
		current_animation = &idle;
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN) {
		current_animation = &spin;
	}
	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN) {
		current_animation = &spin_circle;
	}
	//Only use when App->render->Blit(player_death,...)
	/*if (App->input->keyboard[SDL_SCANCODE_C] == 1) {
	current_animation = &death_circle;
	}*/
	if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_DOWN) {
		App->render->Blit(graphics, position.x, position.y - death.h, &death);
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
		current_animation = &idle;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	App->render->Blit(App->scene_forest->graphics, 202, 0, &App->scene_forest->Templesgate2, 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN) {
		App->particles->AddParticle(App->particles->bullet, position.x, position.y-20);
	}


	return UPDATE_CONTINUE;
}
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleSceneForest.h"


ModulePlayerTwo::ModulePlayerTwo() {
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 30, 2, 32, 32 });
	idle.PushBack({ 64, 2, 32, 32 });
	idle.PushBack({ 97, 2, 32, 32 });
	idle.speed = 0.20f;

	backward.PushBack({ 122, 40, 32, 32 });
	backward.PushBack({ 155, 39, 32, 32 });
	backward.PushBack({ 187, 38, 32, 32 });
	backward.speed = 0.15f;

	intermediate.PushBack({ 5,40,32,32 });
	intermediate.PushBack({ 55,41,32,32 });
	intermediate.PushBack({ 90,40,32,32 });
	intermediate.speed = 0.05f;

	walk.PushBack({ 3,75,32,32 });
	walk.PushBack({ 35,75,32,32 });
	walk.PushBack({ 65,75,32,32 });
	walk.PushBack({ 92,75,32,32 });
	walk.PushBack({ 124,75,32,32 });
	walk.PushBack({ 156,75,32,32 });
	walk.PushBack({ 192,76,30,25 });
	walk.speed = 0.2f;
	
}

ModulePlayerTwo::~ModulePlayerTwo()
{}

// Load assets
bool ModulePlayerTwo::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/sprite/Ayin_Spritesheet.png"); // arcade version
	player_death = App->textures->Load("assets/sprite/Death_Player.png");
	return ret;
}

bool ModulePlayerTwo::CleanUp()
{
	LOG("Unloading Player");
	App->textures->Unload(graphics);
	App->textures->Unload(player_death);

	return true;
}

// Update: draw background
update_status ModulePlayerTwo::Update()
{

	float speed = 2.5;

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT)
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
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE) {
		aux = 0;
	}
	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
		if (position.y == SCREEN_HEIGHT) {
			current_animation = &walk;
		}
		else {
			current_animation = &idle;
		}
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT) {
		if (aux < 30) {
			current_animation = &intermediate;
			aux++;
		}
		else {
			current_animation = &backward;
		}
		position.y -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT) {
		current_animation = &idle;
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN) {
		current_animation = &spin;
	}
	if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN) {
		current_animation = &spin_circle;
	}
	//Only use when App->render->Blit(player_death,...)
	/*if (App->input->keyboard[SDL_SCANCODE_C] == 1) {
	current_animation = &death_circle;
	}*/
	if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_DOWN) {
		App->render->Blit(graphics, position.x, position.y - death.h, &death);
	}

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
		current_animation = &idle;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	App->render->Blit(App->scene_forest->graphics, 202, 0, &App->scene_forest->Templesgate2, 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN) {
		App->particles->AddParticle(App->particles->bullet, position.x, position.y - 20);
	}


	return UPDATE_CONTINUE;
}
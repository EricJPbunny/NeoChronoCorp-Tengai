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
	idle.PushBack({ 36,8,30,28 });
	idle.PushBack({ 110,9,30,28 });
	idle.PushBack({ 73,9,30,27 });
	idle.speed = 0.20f;

	// walk backward animation (arcade sprite sheet)
	backward.PushBack({ 148,8,24,28 });
	backward.PushBack({ 280,9,24,28 });
	backward.PushBack({ 265,54,24,28 });
	backward.speed = 0.15f;

	//Intermediate
	intermediate.PushBack({ 213,9,24,27 });
	intermediate.PushBack({ 181,8,23,28 });
	intermediate.PushBack({ 265,54,24,28 });
	intermediate.speed = 0.10f;

	//Intermediate return
	intermediate_return.PushBack({ 265,54,24,28 });
	intermediate_return.PushBack({ 181,8,23,28 });
	intermediate_return.PushBack({ 213,9,24,27 });
	intermediate_return.speed = 0.10f;

	//Walk
	walk.PushBack({ 244,11,27,24 });
	walk.PushBack({ 222,55,30,27 });
	walk.PushBack({ 311,10,32,25 });
	walk.PushBack({ 8,56,30,25 });
	walk.PushBack({ 46,57,27,24 });
	walk.PushBack({ 79,55,28,26 });
	walk.PushBack({ 112,57,32,25 });
	walk.PushBack({ 149,57,31,25 });
	walk.PushBack({ 187,58,27,24 });
	walk.speed = 0.2f;

	//Spin
	spin.PushBack({ 415,10,19,28 });
	spin.PushBack({ 445,10,16,28 });
	spin.PushBack({ 350,8,22,28 });
	spin.PushBack({ 384,10,18,28 });
	spin.speed = 0.15f;

	//Spin Circle
	spin_circle.PushBack({ 216,166,32,32 });
	spin_circle.PushBack({ 249,162,32,32 });
	spin_circle.PushBack({ 289,161,32,32 });
	spin_circle.PushBack({ 322,161,32,32 });
	spin_circle.PushBack({ 355,161,32,32 });
	spin_circle.PushBack({ 389,161,32,32 });
	spin_circle.PushBack({ 423,161,32,32 });
	spin_circle.PushBack({ 457,161,32,32 });
	spin_circle.PushBack({ 356,196,32,32 });
	spin_circle.speed = 0.40f;

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
	death_circle.speed = 0.8f;

	//Death Player
	death.x = 323;
	death.y = 56;
	death.w = 27;
	death.h = 26;
	
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

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
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
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE) {
		aux = 0;
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) {
		if (position.y == SCREEN_HEIGHT) {
			current_animation = &walk;
		}
		else {
			current_animation = &idle;
		}
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT) {
		if (aux < 30) {
			current_animation = &intermediate;
			aux++;
		}
		else {
			current_animation = &backward;
		}
		position.y -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) {
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

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE) {
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
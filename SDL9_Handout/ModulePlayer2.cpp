#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleSceneForest.h"
#include "ModuleFadeToBlack.h"


ModulePlayerTwo::ModulePlayerTwo() {
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 38,9,29,27 });
	idle.PushBack({ 112,9,29,28 });
	idle.PushBack({ 75,9,29,27 });
	idle.speed = 0.20f;

	// walk backward animation (arcade sprite sheet)
	backward.PushBack({ 148,8,24,28 });
	backward.PushBack({ 280,9,24,28 });
	backward.PushBack({ 265,54,24,28 });
	backward.speed = 0.10f;

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
	walk.speed = 0.20f;

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
	graphics = App->textures->Load("assets/sprite/Sho_Spritesheet.png"); // arcade version
	player_death = App->textures->Load("assets/sprite/Death_Player.png");

	coll = App->collision->AddCollider({20, 20, 32, 32}, COLLIDER_PLAYER);
	position.x = (App->render->camera.x) / SCREEN_SIZE + 50;
	position.y = (App->render->camera.y) / SCREEN_SIZE + 70;
	return ret;
}

bool ModulePlayerTwo::CleanUp()
{
	LOG("Unloading Player");

	if (coll != nullptr)
		coll->to_delete = true;
	App->textures->Unload(graphics);
	App->textures->Unload(player_death);

	return true;
}

// Update: draw background
update_status ModulePlayerTwo::Update()
{

	float speed = 2.5;

	//check state
	CheckState();

	//state actions
	PerformActions();

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) {
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT) {
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) {
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) {
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN) {

		aux1++;
		switch (aux1) {
		case 0:
			App->particles->AddParticle(App->particles->shoot, position.x, position.y - 20, COLLIDER_PLAYER_SHOT);
			break;
		case 1:
			App->particles->AddParticle(App->particles->shoot1, position.x, position.y - 20, COLLIDER_PLAYER_SHOT);
			break;
		case 2:
			App->particles->AddParticle(App->particles->shoot2, position.x, position.y - 20, COLLIDER_PLAYER_SHOT);
			aux1 = 0;
			break;
		}
		
	}

	//Update Collider Position
	coll->SetPos(position.x, position.y - 32);

	if (coll->CheckCollision(App->scene_forest->coll_left->rect)) {
		position.x = App->render->camera.x / SCREEN_SIZE;
	}
	if (coll->CheckCollision(App->scene_forest->coll_right->rect)) {
		position.x = (SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE) - 33;
	}
	if (coll->CheckCollision(App->scene_forest->coll_up->rect)) {
		position.y = 32;
	}
	if (coll->CheckCollision(App->scene_forest->coll_down->rect)) {
		position.y = SCREEN_HEIGHT;
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

void ModulePlayerTwo::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == coll && destroyed == false && App->fade->IsFading() == false)
	{
		if (c1->type == COLLIDER_TYPE::COLLIDER_PLAYER && c2->type == COLLIDER_TYPE::COLLIDER_ENEMY) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE, 70);
		}
		destroyed = true;
	}
}

void ModulePlayerTwo::CheckState()
{
	switch (state)
	{
	case IDLE_2:
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN) {
			state = GO_BACKWARD_2;
			LOG("cambio para atras");
		}
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN && position.y == SCREEN_HEIGHT) {
			state = WALK_2;
			LOG("camina");
		}

		break;

	case GO_BACKWARD_2:

		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_UP) {
			state = BACK_IDLE_2;
		}
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP) {
			state = BACK_IDLE_2;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = BACKWARD_2;
			LOG("combio ara esta atras");
		}
		break;

	case BACKWARD_2:

		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_UP) {
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) {
				state = BACK_IDLE_2;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP) {
			if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE) {
				state = BACK_IDLE_2;
			}
		}
		break;

	case BACK_IDLE_2:

		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT) {
			state = BACK_IDLE_2;
		}
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) {
			state = BACK_IDLE_2;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && position.y == SCREEN_HEIGHT) {
				state = WALK_2;
			}
			else {
				state = IDLE_2;
			}
		}
		break;

	case WALK_2:
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_UP) {
			if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN) {
				state = GO_BACKWARD_2;
			}
			else {
				state = IDLE_2;
			}

		}
		break;
	case SPIN_2:
		if (spin.Finished()) {
			state = IDLE_2;
		}
		break;
	}
}

void ModulePlayerTwo::PerformActions()
{
	switch (state) {
	case IDLE_2:
		spin.Reset();
		current_animation = &idle;
		break;

	case GO_BACKWARD_2:
		if (intermediate.Finished())
		{
			intermediate.Reset();
		}
		current_animation = &intermediate;
		break;

	case BACKWARD_2:
		if (backward.Finished())
			backward.Reset();
		current_animation = &backward;
		break;

	case BACK_IDLE_2:
		if (intermediate_return.Finished())
			intermediate_return.Reset();
		current_animation = &intermediate_return;
		break;

	case WALK_2:
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A]) {
			state = IDLE_2;
		}
		if (walk.Finished())
			walk.Reset();
		current_animation = &walk;
		break;
	case SPIN_2:
		SDL_Rect spin_rect = spin_circle.GetCurrentFrame();
		App->render->Blit(graphics, position.x, position.y - 32, &spin_rect);
		current_animation = &spin;
	}


}

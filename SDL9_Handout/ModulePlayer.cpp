#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneForest.h"
#include "ModulePlayer.h"
#include "ModulePartner.h"
#include "ModuleUI.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 300;
	position.y = 300;

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
	intermediate.speed = 0.10f;

	//Intermediate return
	intermediate_return.PushBack({ 270,95,26,29 });
	intermediate_return.PushBack({ 230,95,24,28 });
	intermediate_return.PushBack({ 187,95,27,29 });
	intermediate_return.speed = 0.10f;

	//Walk
	walk.PushBack({ 74,12,27,27 });
	walk.PushBack({ 114,13,27,27 });
	walk.PushBack({ 153,11,27,29 });
	walk.PushBack({ 194,8,27,32 });
	walk.PushBack({ 234,9,28,30 });
	walk.PushBack({ 274,12,28,28 });
	walk.PushBack({ 313,15,30,25 });
	walk.speed = 0.20f;

	//Spin
	spin.PushBack({ 22,95,33,29 });
	spin.PushBack({ 62,95,26,29 });
	spin.PushBack({ 102,95,30,29 });
	spin.PushBack({ 142,95,28,29 });
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
	spin_circle.speed = 0.3f;

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
	graphics = App->textures->Load("assets/sprite/miko.png"); // arcade version
	player_death = App->textures->Load("assets/sprite/Death_Player.png");

	coll = App->collision->AddCollider({ (int)position.x, (int)position.y, 32, 32 }, COLLIDER_PLAYER);

	position.x = (App->render->camera.x) / SCREEN_SIZE + 50;
	position.y = (App->render->camera.y) / SCREEN_SIZE + 70;

	state = IDLE;

	App->partner->Enable();

	destroyed = false;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(player_death);
	if (coll != nullptr)
		coll->to_delete = true;

	App->partner->Disable();
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	float speed = 2.5;

	//check state
	CheckState();

	//state actions
	PerformActions();

	//Inputs
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		aux1++;
		switch (aux1) {
		case 0:
			App->particles->AddParticle(App->particles->bullet, position.x, position.y - 20, COLLIDER_PLAYER_SHOT,PARTICLE_SHOT);
			break;
		case 1:
			App->particles->AddParticle(App->particles->bullet2, position.x, position.y - 20, COLLIDER_PLAYER_SHOT, PARTICLE_SHOT);
			break;
		case 2:
			App->particles->AddParticle(App->particles->bullet3, position.x, position.y - 20, COLLIDER_PLAYER_SHOT, PARTICLE_SHOT);
			break;
		case 3:
			App->particles->AddParticle(App->particles->bullet4, position.x, position.y - 20, COLLIDER_PLAYER_SHOT, PARTICLE_SHOT);
			break;
		case 4:
			App->particles->AddParticle(App->particles->bullet5, position.x, position.y - 20, COLLIDER_PLAYER_SHOT, PARTICLE_SHOT);
			aux1 = 0;
			break;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {
		App->ui->num_life_koyori = 0;
	}

	//Check Death
	if (App->ui->num_life_koyori == 0) {
		state = DEATH;
	}
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	if (!check_death) {
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
		//Update Collider Position
		coll->SetPos(position.x, position.y - 32);
	}
	if (check_death) {
		App->render->Blit(graphics, position.x, position.y - 32, &death);
		coll->SetPos(App->render->camera.x, App->render->camera.y - 32);
		position.x -= 1;
		position.y += 3;
	}
	//temple
	App->render->Blit(App->scene_forest->graphics, 202, 0, &App->scene_forest->Templesgate2, 0.75f);

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

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == coll && destroyed == false && App->fade->IsFading() == false)
	{
		if (c1->type==COLLIDER_TYPE::COLLIDER_PLAYER_SHOT && c2->type==COLLIDER_TYPE::COLLIDER_ENEMY) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE, PARTICLE_NONE, 70);
		}
		destroyed = true;
	}
}

void ModulePlayer::CheckState()
{
	switch (state)
	{
	case IDLE:
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN) {
			state = GO_BACKWARD;
			LOG("cambio para atras");
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN && position.y == SCREEN_HEIGHT) {
			state = WALK;
			LOG("camina");
		}

		break;

	case GO_BACKWARD:
		
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP) {
			state = BACK_IDLE;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
			state = BACK_IDLE;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = BACKWARD;
			LOG("combio ara esta atras");
		}
		break;

	case BACKWARD:
		
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP) {
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) {
				state = BACK_IDLE;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) {
				state = BACK_IDLE;
			}
		}
		break;

	case BACK_IDLE:

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
			state = BACK_IDLE;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
			state = BACK_IDLE;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && position.y == SCREEN_HEIGHT) {
				state = WALK;
			}
			else {
				state = IDLE;
			}
		}
		break;

	case WALK:
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A]) {
			state = IDLE;
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP) {
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) {
				state = GO_BACKWARD;
			}
			else {
				state = IDLE;
			}
		}
		break;
	case SPIN:
		if (spin.Finished()) {
			spin.Reset();
			spin_circle.Reset();
			state = IDLE;
		}
		break;
	case DEATH:
		if (position.y > SCREEN_HEIGHT+80) {
			state = POST_DEATH;
		}
		break;
	}
}

void ModulePlayer::PerformActions()
{
	switch (state) {
	case IDLE:
		check_death = false;
		spin.Reset();
		current_animation = &idle;
		break;

	case GO_BACKWARD:
		if (intermediate.Finished())
		{
			intermediate.Reset();
		}
		current_animation = &intermediate;
		break;

	case BACKWARD:
		if (backward.Finished())
			backward.Reset();
		current_animation = &backward;
		break;

	case BACK_IDLE:
		if (intermediate_return.Finished())
			intermediate_return.Reset();
		current_animation = &intermediate_return;
		break;

	case WALK:
		if (walk.Finished())
			walk.Reset();
		current_animation = &walk;
		break;
	case SPIN:
		SDL_Rect spin_rect = spin_circle.GetCurrentFrame();
		App->render->Blit(graphics, position.x+1, position.y-32, &spin_rect);
		current_animation = &spin;
		break;
	case DEATH:
		check_death = true;
		break;
	case POST_DEATH:
		App->player->Disable();
		break;
	}
	

	
}

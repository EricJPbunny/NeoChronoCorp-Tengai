#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneForest.h"
#include "ModulePlayer.h"
#include "ModulePartner.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"


#include "SDL\include\SDL_timer.h"
#include "SDL\include\SDL_render.h"

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
	hitbox = App->collision->AddCollider({ (int)position.x, (int)position.y,16,16 }, COLLIDER_HITBOX);

	position.x = (App->render->camera.x) / SCREEN_SIZE-20;
	position.y = (App->render->camera.y) / SCREEN_SIZE+100;

	state = SPAWN_PLAYER;
	App->ui->num_life_koyori = 4;
	power_up = 0;

	k_power_down = App->audio->LoadEffect("assets/audio/koyori_lvl_down.wav");
	death_fx = App->audio->LoadEffect("assets/audio/death_koyori.wav");

	App->partner->Enable();
	time = true;
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

	if (hitbox != nullptr)
		hitbox->to_delete = true;

	App->ui->game_over_koyori = true;

	App->audio->UnloadFx(death_fx);
	App->audio->UnloadFx(k_power_down);

	App->partner->Disable();
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	float speed = 2.5;

	//Power Up Limits
	if (power_up < 0) {
		power_up = 0;
	}
	if (power_up > 2) {
		power_up = 2;
	}

	//check state
	CheckState();

	//state actions
	PerformActions();

	//Inputs
	if (input) {
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
				App->particles->AddParticle(App->particles->bullet, position.x, position.y - 20, COLLIDER_PLAYER_SHOT, PARTICLE_SHOT);
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
	}
	//Fade
	SDL_SetTextureAlphaMod(graphics, alpha_player);
	//Check Death
	if (App->ui->num_life_koyori == 0) {
		state = DEATH;
	}

	//Set spin posotion
	if (spin_pos) {
		aux_spin.x = position.x + 5;
		aux_spin.y = position.y - 32;
		spin_pos = false;
	}

	if (death_pos) {
		aux_death.x = position.x - 40;
		aux_death.y = position.y - 70;
		death_pos = false;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	if (!check_death) {
		if (check_spawn) {
			position.x++;
			coll->SetPos(App->render->camera.x, App->render->camera.y - 32);
		}
		else {
			coll->SetPos(position.x, position.y - 32);
			hitbox->SetPos(position.x+8, position.y-20);
		}
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}
	else {
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
		position.y = 52;
	}
	if (coll->CheckCollision(App->scene_forest->coll_down->rect)) {
		position.y = SCREEN_HEIGHT-4;
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	
}

void ModulePlayer::CheckState()
{
	switch (state)
	{
	case SPAWN_PLAYER:
		if (time) {
			time_on_entry = SDL_GetTicks();
			time = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1500) {
			state = IDLE;
		}
		
		break;

	case IDLE:
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN) {
			state = GO_BACKWARD;
			LOG("cambio para atras");
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN && position.y == SCREEN_HEIGHT-4) {
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
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && position.y == SCREEN_HEIGHT-4) {
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
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && position.y == SCREEN_HEIGHT - 4) {
			current_animation = &walk;
		}
		else { current_animation = &idle; }
		if (App->render->camera.x > 26000) {
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && position.y == SCREEN_HEIGHT - 4) {
				current_animation = &idle;
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
	case SPAWN_PLAYER:
		App->ui->game_over_koyori = false;
		check_spawn = true;
		current_animation = &idle;
		blink_time = SDL_GetTicks() - blink_on_entry;
		if (blink_time > 10) {
			blink_on_entry = SDL_GetTicks();
			if (blink) {
				alpha_player = 0;
				blink = false;
			}
			else {
				alpha_player = 255;
				blink = true;
			}
		}
		input = false;
		check_death = false;
		break;

	case IDLE:
		input = true;
		death_pos = true;
		check_spawn = false;
		alpha_player = 255;
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
		break;

	case SPIN:
		SDL_Rect spin_rect = spin_circle.GetCurrentFrame();
		App->render->Blit(graphics, aux_spin.x, aux_spin.y, &spin_rect);
		current_animation = &spin;
		break;

	case DEATH:
		SDL_Rect death_rect = death_circle.GetCurrentFrame();
		check_death = true;
		input = false;
		App->render->Blit(player_death, aux_death.x, aux_death.y, &death_rect,1.0f);
		alpha_player = 255;
		break;

	case POST_DEATH:
		App->player->Disable();
		break;
	}	
}

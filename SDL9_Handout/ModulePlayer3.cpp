#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneAir.h"
#include "ModulePlayer3.h"
#include "ModulePartner.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"

#include "SDL\include\SDL_timer.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_joystick.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer3::ModulePlayer3()
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

ModulePlayer3::~ModulePlayer3()
{}

// Load assets
bool ModulePlayer3::Start()
{
	LOG("Loading player textures");
	graphics = App->textures->Load("assets/sprite/miko.png"); // arcade version
	player_death = App->textures->Load("assets/sprite/Death_Player.png");

	coll = App->collision->AddCollider({ (int)position.x, (int)position.y, 32, 32 }, COLLIDER_PLAYER);
	hitbox = App->collision->AddCollider({ (int)position.x, (int)position.y,16,16 }, COLLIDER_HITBOX);

	position.x = (App->render->camera.x) / SCREEN_SIZE-20;
	position.y = (App->render->camera.y) / SCREEN_SIZE+100;

	state = SPAWN_PLAYER_3;

	k_power_down = App->audio->LoadEffect("assets/audio/koyori_lvl_down.wav");

	App->ui->num_life_koyori = 3;

	App->partner->Enable();
	time = true;
	destroyed = false;
	return true;
}

// Unload assets
bool ModulePlayer3::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(player_death);
	if (coll != nullptr)
		coll->to_delete = true;

	if (hitbox != nullptr)
		hitbox->to_delete = true;

	App->ui->game_over_koyori = true;

	App->audio->UnloadFx(k_power_down);

	App->partner->Disable();
	return true;
}

// Update: draw background
update_status ModulePlayer3::Update()
{
	float speed = 2.5;

	//Create bool variables
	bool pressed_up = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT;
	bool pressed_left = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT;
	bool pressed_down = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT;
	bool pressed_right = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT;

	bool shot_ctrl = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN;

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

	if (input) {
		if (pressed_left) {
			position.x -= speed;
		}
		if (pressed_up) {
			position.y -= speed;
		}
		if (pressed_right) {
			position.x += speed;
		}
		if (pressed_down) {
			position.y += speed;
		}

		if (shot_ctrl) {
			aux1++;
			switch (aux1) {
			case 0:
				App->particles->AddParticle(App->particles->shoot, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				break;
			case 1:
				App->particles->AddParticle(App->particles->shoot1, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				break;
			case 2:
				App->particles->AddParticle(App->particles->shoot2, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				aux1 = 0;
				break;
			}

		}
	}
	
	//Fade
	SDL_SetTextureAlphaMod(graphics, alpha_player);

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

			if (!App->scene_air->god_mode)
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


	if (coll->CheckCollision(App->scene_air->coll_left->rect)) {
		position.x = App->render->camera.x / SCREEN_SIZE;
	}
	if (coll->CheckCollision(App->scene_air->coll_right->rect)) {
		position.x = (SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE) - 33;
	}
	if (coll->CheckCollision(App->scene_air->coll_up->rect)) {
		position.y = 52;
	}
	if (coll->CheckCollision(App->scene_air->coll_down->rect)) {
		position.y = SCREEN_HEIGHT-4;
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer3::OnCollision(Collider* c1, Collider* c2)
{
	
}

void ModulePlayer3::CheckState()
{
	//Create Input Bools
	bool pressed_left = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT;
	bool pressed_up = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT;

	bool press_left = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN;
	bool press_up = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN;

	bool release_left = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP;
	bool release_up = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_UP;

	bool released_up = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE;
	bool released_left = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE;

	switch (state)
	{
	case SPAWN_PLAYER_3:
		if (time) {
			time_on_entry = SDL_GetTicks();
			time = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1500) {
			state = IDLE_3;
		}
		power_up = 0;
		break;

	case IDLE_3:
		if (press_left || press_up) {
			state = GO_BACKWARD_3;
		}

		break;

	case GO_BACKWARD_3:

		if (release_up) {
			state = BACK_IDLE_3;
		}
		if (release_left) {
			state = BACK_IDLE_3;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = BACKWARD_3;
		}
		break;

	case BACKWARD_3:
		if (release_up || release_left) {
			if (released_left || released_up) {
				state = BACK_IDLE_3;
			}
		}
		break;

	case BACK_IDLE_3:
		if (pressed_up) {
			state = BACK_IDLE_3;
		}
		if (pressed_left) {
			state = BACK_IDLE_3;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = IDLE_3;
		}
		break;

	case SPIN_3:
		if (spin.Finished()) {
			spin.Reset();
			spin_circle.Reset();
			state = IDLE_3;
		}
		break;

	case DEATH_3:
		if (position.y > SCREEN_HEIGHT + 80) {
			state = POST_DEATH_3;
		}
		break;

	case POST_DEATH_3:
		if (App->ui->num_life_sho > 0) {
			position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
			position.y = (App->render->camera.y) / SCREEN_SIZE + 100;
			time = true;
			state = SPAWN_PLAYER_3;
		}
		break;
	}
}

void ModulePlayer3::PerformActions()
{
	switch (state) {
	case SPAWN_PLAYER_3:
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

	case IDLE_3:
		if (App->render->camera.x > 51200) {
			input = false;
		}
		if (App->render->camera.x < 51200) {
			input = true;
		}
		death_pos = true;
		check_spawn = false;
		alpha_player = 255;
		spin.Reset();
		current_animation = &idle;
		break;

	case GO_BACKWARD_3:
		
		if (intermediate.Finished())
		{
			intermediate.Reset();
		}
		current_animation = &intermediate;
		break;

	case BACKWARD_3:
		
		if (backward.Finished())
			backward.Reset();
		current_animation = &backward;
		break;

	case BACK_IDLE_3:
		
		if (intermediate_return.Finished())
			intermediate_return.Reset();
		current_animation = &intermediate_return;
		break;

	case SPIN_3:
		SDL_Rect spin_rect = spin_circle.GetCurrentFrame();
		App->render->Blit(graphics, aux_spin.x, aux_spin.y, &spin_rect);
		current_animation = &spin;
		break;

	case DEATH_3:
		SDL_Rect death_rect = death_circle.GetCurrentFrame();
		power_up = 0;
		check_death = true;
		input = false;
		App->render->Blit(player_death, aux_death.x, aux_death.y, &death_rect,1.0f);
		if (explosion) {
 			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			explosion = false;
		}
		alpha_player = 255;
		break;

	case POST_DEATH_3:
		if (App->ui->num_life_koyori == 0) {
			if (App->ui->score_koyori > 1000) {
				App->ui->score_koyori -= 1000;
			}
			App->player->Disable();
		}
		else {
			check_death = false;
		}
		break;
	}	
}

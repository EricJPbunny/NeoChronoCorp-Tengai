#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModulePartner2.h"
#include "ModuleSceneSelect.h"
#include "ModuleUlti2.h"
#include "ModuleSceneAir.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"

#include "SDL\include\SDL_timer.h"
#include "SDL\include\SDL_render.h"


ModulePlayerTwo::ModulePlayerTwo() {
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 180;

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

	//Spin
	spin.PushBack({ 415,10,19,28 });
	spin.PushBack({ 445,10,16,28 });
	spin.PushBack({ 350,8,22,28 });
	spin.PushBack({ 384,10,18,28 });
	spin.PushBack({ 415,10,19,28 });
	spin.PushBack({ 445,10,16,28 });
	spin.PushBack({ 350,8,22,28 });
	spin.PushBack({ 384,10,18,28 });
	spin.speed = 0.15f;

	//Spin Circle
	spin_circle.PushBack({ 212,161,32,32 });
	spin_circle.PushBack({ 249,161,32,32 });
	spin_circle.PushBack({ 290,161,32,32 });
	spin_circle.PushBack({ 323,161,32,32 });
	spin_circle.PushBack({ 356,161,32,32 });
	spin_circle.PushBack({ 390,161,32,32 });
	spin_circle.PushBack({ 424,161,32,32 });
	spin_circle.PushBack({ 458,161,32,32 });
	spin_circle.PushBack({ 214,192,32,32 });
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
	graphics = App->textures->Load("assets/sprite/Sho_Spritesheet.png"); // arcade version
	player_death = App->textures->Load("assets/sprite/Death_Player.png");

	coll = App->collision->AddCollider({ (int)position.x, (int)position.y, 32, 32 }, COLLIDER_PLAYER);
	hitbox = App->collision->AddCollider({ (int)position.x, (int)position.y,16,16 }, COLLIDER_HITBOX);

	position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
	position.y = (App->render->camera.y) / SCREEN_SIZE + 100;

	state = SPAWN_PLAYER_2;

	App->partner2->Enable();

	App->ui->num_life_sho = 3;

	time = true;
	destroyed = false;
	return true;
}

bool ModulePlayerTwo::CleanUp()
{
	LOG("Unloading Player");

	if (coll != nullptr)
		coll->to_delete = true;

	if (hitbox != nullptr)
		hitbox->to_delete = true;

	App->textures->Unload(graphics);
	App->textures->Unload(player_death);

	App->partner2->Disable();

	App->ui->game_over_sho = true;

	return true;
}

// Update: draw background
update_status ModulePlayerTwo::Update()
{
	if (App->scene_select->sho_p1) {
		//Create bool variables
		pressed_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEADZONE;
		pressed_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEADZONE;
		pressed_S = App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller, SDL_CONTROLLER_AXIS_LEFTY) > CONTROLLER_DEADZONE;
		pressed_D = App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEADZONE;

		shot_space = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ;
		ulti_button = App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_DOWN || App->input->controller_X_button == KEY_STATE::KEY_DOWN;
	}
	else {
		pressed_W = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEADZONE;
		pressed_A = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEADZONE;
		pressed_S = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTY) > CONTROLLER_DEADZONE;
		pressed_D = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->controller2, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEADZONE;

		shot_space = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN ;
		ulti_button = App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN || App->input->controller_X_button2 == KEY_STATE::KEY_DOWN;
	}

	float speed = 2.5;

	//Power Up Limits
	if (power_up < 0) {
		power_up = 0;
	}
	if (power_up > 4) {
		power_up = 4;
	}

	//check state
	CheckState();

	//state actions
	PerformActions();

	//Inputs
	if (input) {
		if (pressed_A) {
			position.x -= speed;
		}
		if (pressed_W) {
			position.y -= speed;
		}
		if (pressed_D) {
			position.x += speed;
		}
		if (pressed_S) {
			position.y += speed;
		}

		if (ulti_button && App->ui->num_ulti_sho > 0) {
			if (!App->ulti2->IsEnabled()) {
				App->ui->num_ulti_sho--;
				App->ulti2->timer = true;
				App->ulti2->Enable();
			}
		}
		if (App->scene_select->sho_p1) {
			key = App->input->controller_A_button == KEY_STATE::KEY_DOWN;
		}
		else {
			key = App->input->controller_A_button2 == KEY_STATE::KEY_DOWN;
		}
		if (shot_space || key) {
		
			switch (aux1) {
			case 0:
				if (power_up == 3) {
					App->particles->AddParticle(App->particles->shoot_sho_big, position.x + 6, position.y - 14, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big, position.x + 6, position.y - 24, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				else if (power_up == 4) {
					App->particles->AddParticle(App->particles->shoot_sho_big, position.x + 6, position.y - 31, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big, position.x + 16, position.y - 24, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big, position.x + 16, position.y - 17, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big, position.x + 6, position.y - 10 , COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
  				else if (power_up == 1 || power_up == 2) {
					App->particles->AddParticle(App->particles->shoot_sho_big, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				else {
					App->particles->AddParticle(App->particles->shoot_sho_big, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				break;
			case 1:
				if (power_up == 3) {
					App->particles->AddParticle(App->particles->shoot_sho_big_1, position.x + 6, position.y - 14, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big_1, position.x + 6, position.y - 24, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				else if (power_up == 4) {
					App->particles->AddParticle(App->particles->shoot_sho_big_1, position.x, position.y - 5, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big_1, position.x+5, position.y -10, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big_1, position.x+5, position.y - 15, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big_1, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				else if (power_up == 1 || power_up == 2) {
					App->particles->AddParticle(App->particles->shoot_sho_big_1, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				else {
					App->particles->AddParticle(App->particles->shoot1, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				break;
			case 2:
				if (power_up == 3) {
					App->particles->AddParticle(App->particles->shoot_sho_big_2, position.x + 6, position.y - 14, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big_2, position.x + 6, position.y - 24, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				else if (power_up == 4) {
					App->particles->AddParticle(App->particles->shoot_sho_big_2, position.x, position.y -5, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big_2, position.x + 5, position.y -10, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big_2, position.x + 5, position.y - 15, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
					App->particles->AddParticle(App->particles->shoot_sho_big_2, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				else if (power_up == 1 || power_up == 2) {
					App->particles->AddParticle(App->particles->shoot_sho_big_2, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				else {
					App->particles->AddParticle(App->particles->shoot2, position.x, position.y - 20, COLLIDER_PLAYER_2_SHOT, PARTICLE_SHOT_2);
				}
				aux1 = 0;
				break;
			}
		}
	}
	//Fade
	SDL_SetTextureAlphaMod(graphics, alpha_player);

	//Check Death
	if (App->ui->num_life_sho == 0) {
		state = DEATH_2;
	}

	//Set spin posotion
	if (spin_pos) {
		aux_spin.x = position.x + 5;
		aux_spin.y = position.y-32;
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
				hitbox->SetPos(position.x + 8, position.y - 20);
		}
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}
	else {
		App->render->Blit(graphics, position.x, position.y - 32, &death);
		coll->SetPos(App->render->camera.x, App->render->camera.y - 32);
		hitbox->SetPos(App->render->camera.x, App->render->camera.y - 32);

		position.x -= 1;
		position.y += 3;
	}

	if (coll->CheckCollision(App->scene_air->coll_left->rect)) {
		position.x = (App->render->camera.x / SCREEN_SIZE);
	}
	if (coll->CheckCollision(App->scene_air->coll_right->rect)) {
		position.x = (SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE) - 33;
	}
	if (coll->CheckCollision(App->scene_air->coll_up->rect)) {
		position.y = 52 + App->render->camera.y / SCREEN_SIZE;
	}
	if (coll->CheckCollision(App->scene_air->coll_down->rect)) {
		position.y = SCREEN_HEIGHT - 4 + App->render->camera.y / SCREEN_SIZE;
	}
	return UPDATE_CONTINUE;
}

void ModulePlayerTwo::OnCollision(Collider* c1, Collider* c2)
{
	
}

void ModulePlayerTwo::CheckState()
{

	if (App->scene_select->sho_p1) {
		//Create bool variables
		press_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN;
		press_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN;

		release_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP;
		release_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP;

		released_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE;
		released_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE;
	}
	else {
		press_A = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN;
		press_W = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN;

		release_A = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP;
		release_W = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_UP;

		released_W = App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE;
		released_A = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE;
	}

	switch (state)
	{
	case SPAWN_PLAYER_2:
		App->ui->enemies_movement = true;
		if (time) {
			time_on_entry = SDL_GetTicks();
			time = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1500) {
			state = IDLE_2;
		}
		App->ui->num_ulti_sho = 2;
		power_up = 0;
		break;

	case IDLE_2:
		if (press_W || press_A) {
			state = GO_BACKWARD_2;
		}

		break;

	case GO_BACKWARD_2:

		if (release_W) {
			state = BACK_IDLE_2;
		}
		if (release_A) {
			state = BACK_IDLE_2;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = BACKWARD_2;
		}
		break;

	case BACKWARD_2:
		if (release_W || release_A) {
			if (released_W || released_A) {
				state = BACK_IDLE_2;
			}
		}
		break;

	case BACK_IDLE_2:
		if (pressed_W) {
			state = BACK_IDLE_2;
		}
		if (pressed_A) {
			state = BACK_IDLE_2;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = IDLE_2;
		}
		break;

	case SPIN_2:
		if (spin.Finished()) {
			spin.Reset();
			spin_circle.Reset();
			state = IDLE_2;
		}
		break;

	case DEATH_2:
		if (position.y > (App->render->camera.y) / SCREEN_SIZE + 400) {
			state = POST_DEATH_2;
		}
		break;

	case POST_DEATH_2:
		if (App->ui->num_life_sho > 0) {
			position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
			position.y = (App->render->camera.y) / SCREEN_SIZE + 100;
			time = true;
			state = SPAWN_PLAYER_2;
		}
		break;
	}
}

void ModulePlayerTwo::PerformActions()
{
	switch (state) {
	case SPAWN_PLAYER_2:
		App->ui->game_over_sho = false;
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
		check_death = false;
		input = false;
		break;

	case IDLE_2:
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

	case SPIN_2:
		SDL_Rect spin_rect = spin_circle.GetCurrentFrame();
		App->render->Blit(graphics, aux_spin.x, aux_spin.y, &spin_rect);
		current_animation = &spin;
		break;

	case DEATH_2:
		SDL_Rect death_rect = death_circle.GetCurrentFrame();
		power_up = 0;
		check_death = true;
		input = false;
		App->render->Blit(player_death, aux_death.x, aux_death.y, &death_rect, 1.0f);
		if (explosion) {
			App->particles->AddParticle(App->particles->explosion, position.x-8, position.y-8);
			explosion = false;
		}
		alpha_player = 255;
		break;

	case POST_DEATH_2:
		if (App->ui->num_life_sho == 0) {
			if (App->ui->score_sho > 1000) {
				App->ui->score_sho -= 1000;
			}
			App->player2->Disable();
		}
		else {
			check_death = false;
		}
		break;
	}
}

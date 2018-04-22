#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModulePartner2.h"
#include "ModuleSceneForest.h"
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
	bool ret = true;
	graphics = App->textures->Load("assets/sprite/Sho_Spritesheet.png"); // arcade version
	player_death = App->textures->Load("assets/sprite/Death_Player.png");

	App->partner2->Enable();
	input = true;
	state = SPAWN_PLAYER_2;
	App->ui->num_life_sho = 3;
	power_up = 0;

	coll = App->collision->AddCollider({ (int)position.x, (int)position.y, 32, 32}, COLLIDER_PLAYER);
	hitbox = App->collision->AddCollider({ (int)position.x, (int)position.y,16,16 }, COLLIDER_HITBOX_2);

	position.x = (App->render->camera.x) / SCREEN_SIZE-20;
	position.y = (App->render->camera.y) / SCREEN_SIZE + 100;
	return ret;
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

	time = true;
	App->ui->game_over_sho = true;
	check_death = true;

	return true;
}

// Update: draw background
update_status ModulePlayerTwo::Update()
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
	if (input) {
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

		if (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN) {

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
	//Update Collider Position

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


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	if (!check_death) {
		if (check_spawn) {
			position.x++;
			coll->SetPos(App->render->camera.x, App->render->camera.y - 100);
		}
		else {
			coll->SetPos(position.x, position.y - 32);
			hitbox->SetPos(position.x + 8, position.y - 20);
		}
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}
	if (check_death) {
		App->render->Blit(graphics, position.x, position.y - 32, &death);
		coll->SetPos(App->render->camera.x, App->render->camera.y - 32);
		position.x -= 1;
		position.y += 3;
	}

	//Temple
	App->render->Blit(App->scene_forest->graphics, 202, 0, &App->scene_forest->Templesgate2, 0.75f);


	

	return UPDATE_CONTINUE;
}

void ModulePlayerTwo::OnCollision(Collider* c1, Collider* c2)
{
	
}

void ModulePlayerTwo::CheckState()
{
	switch (state)
	{
	case SPAWN_PLAYER_2:
		if (time) {
			time_on_entry = SDL_GetTicks();
			time = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1500) {
			state = IDLE_2;
		}
		break;

	case IDLE_2:
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN) {
			state = GO_BACKWARD_2;
		}
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN && position.y == SCREEN_HEIGHT-4) {
			state = WALK_2;
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
			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && position.y == SCREEN_HEIGHT-4) {
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
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && position.y == SCREEN_HEIGHT - 4) {
			current_animation = &walk;
		}
		else { current_animation = &idle; }
		if (App->render->camera.x > 26000) {
			if (walk.Finished())
				walk.Reset();
			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && position.y == SCREEN_HEIGHT - 4) {
				current_animation = &idle;
			}
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
		if (position.y > SCREEN_HEIGHT + 80) {
			state = POST_DEATH_2;
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
		input = true;
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

	case WALK_2:
		if (walk.Finished())
			walk.Reset();
		break;

	case SPIN_2:
		SDL_Rect spin_rect = spin_circle.GetCurrentFrame();
		App->render->Blit(graphics, aux_spin.x, aux_spin.y, &spin_rect);
		current_animation = &spin;
		break;

	case DEATH:
		check_death = true;
		alpha_player = 255;
		break;

	case POST_DEATH:
		App->player2->Disable();
		break;
	}


}

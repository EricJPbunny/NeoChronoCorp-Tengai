#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneAir.h"
#include "ModulePlayer2.h"
#include "ModulePartner2.h"
#include "ModuleSceneSelect.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"


#include "SDL\include\SDL_timer.h"


ModulePartner2::ModulePartner2()
{
	graphics = nullptr;
	current_animation = nullptr;

	spawn.PushBack({ 6,146,10,11 });
	spawn.PushBack({ 19,146,10,11 });
	spawn.PushBack({ 31,146,10,11 });
	spawn.PushBack({ 51,147,10,11 });
	spawn.speed = 0.30f;

	spawn2.PushBack({ 6,146,10,11 });
	spawn2.PushBack({ 19,146,10,11 });
	spawn2.PushBack({ 31,146,10,11 });
	spawn2.PushBack({ 51,147,10,11 });
	spawn2.speed = 0.30f;

	spawn3.PushBack({ 6,146,10,11 });
	spawn3.PushBack({ 19,146,10,11 });
	spawn3.PushBack({ 31,146,10,11 });
	spawn3.PushBack({ 51,147,10,11 });
	spawn3.speed = 0.30f;

	spawn4.PushBack({ 6,146,10,11 });
	spawn4.PushBack({ 19,146,10,11 });
	spawn4.PushBack({ 31,146,10,11 });
	spawn4.PushBack({ 51,147,10,11 });
	spawn4.speed = 0.30f;

	spawn_reverse.PushBack({ 51,147,10,11 });
	spawn_reverse.PushBack({ 31,146,10,11 });
	spawn_reverse.PushBack({ 19,146,10,11 });
	spawn_reverse.PushBack({ 6,146,10,11 });
	spawn_reverse.speed = 0.30f;

	spawn_reverse2.PushBack({ 51,147,10,11 });
	spawn_reverse2.PushBack({ 31,146,10,11 });
	spawn_reverse2.PushBack({ 19,146,10,11 });
	spawn_reverse2.PushBack({ 6,146,10,11 });
	spawn_reverse2.speed = 0.30f;

	spawn_reverse3.PushBack({ 51,147,10,11 });
	spawn_reverse3.PushBack({ 31,146,10,11 });
	spawn_reverse3.PushBack({ 19,146,10,11 });
	spawn_reverse3.PushBack({ 6,146,10,11 });
	spawn_reverse3.speed = 0.30f;

	spawn_reverse4.PushBack({ 51,147,10,11 });
	spawn_reverse4.PushBack({ 31,146,10,11 });
	spawn_reverse4.PushBack({ 19,146,10,11 });
	spawn_reverse4.PushBack({ 6,146,10,11 });
	spawn_reverse4.speed = 0.30f;

	iddle.PushBack({ 123,175,15,13 });
	iddle.PushBack({ 148,175,15,13 });
	iddle.PushBack({ 171,175,15,13 });
	iddle.PushBack({ 193,175,15,13 });
	iddle.speed = 0.05f;

	charging.PushBack({ 5,175,25,13 });
	charging.PushBack({ 35,175,24,13 });
	charging.PushBack({ 64,175,23,13 });
	charging.PushBack({ 92,175,22,13 });
	charging.speed = 0.10f;

}

ModulePartner2::~ModulePartner2()
{
	//destroyer
}

bool ModulePartner2::Start()
{
	LOG("Loading partner textures");
	graphics = App->textures->Load("assets/sprite/Sho_Spritesheet.png");
	if (graphics == nullptr)
	{
		LOG("Could not load partner textures")
			return false;
	}
	position.x = App->player2->position.x;
	position.y = App->player2->position.y;
	charged_mirror = App->audio->LoadEffect("assets/audio/charged_mirror.wav");
	release_mirror = App->audio->LoadEffect("assets/audio/charged_mirror.wav");
	return true;
}

bool ModulePartner2::CleanUp()
{
	LOG("Unloading player");
	App->audio->UnloadFx(release_mirror);
	App->audio->UnloadFx(charged_mirror);
	App->textures->Unload(graphics);
	if (graphics != nullptr)
	{
		LOG("Could not unload partner 2 textures")
			return false;
	}

	return true;
}

update_status ModulePartner2::Update()
{
	//Create bool variables
	if (App->scene_select->sho_p1) {
		shot_space = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->controller_A_button == KEY_STATE::KEY_DOWN;
	}
	else {
		shot_space = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN || App->input->controller_A_button2 == KEY_STATE::KEY_DOWN;
	}

	//check state
	CheckState();

	//state actions
	PerformActions();

	//Prove
	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN) {
		App->player2->power_up++;
	}
	if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN) {
		App->player2->power_up--;
	}

	//Set Position
	if (movement) {
		position.x = App->player2->position.x - 25;
		position.y = App->player2->position.y - 10;
	}
	if (!movement && !charged_shoot) {
		position.x = App->player2->position.x + 25;
		position.y = App->player2->position.y - 20;
	}
	else if (charged_shoot) {
		position.x += App->scene_air->speed / SCREEN_SIZE;
	}

	//Draw Partner
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect r1 = current_animation_2->GetCurrentFrame();
	SDL_Rect r2 = current_animation_3->GetCurrentFrame();
	SDL_Rect r3 = current_animation_4->GetCurrentFrame();

	if (exist) {
		if (movement) {
			if (shot_space) {
				if (shot_delay)
				{
					shot_entry = SDL_GetTicks();
					shot_delay = false;
				}
				shot_current = SDL_GetTicks() - shot_entry;
				if (shot_current > 300) {
					App->particles->AddParticle(App->particles->mirror_shoot, position.x + 10, position.y - 26, COLLIDER_PLAYER_2_SHOT);
					shot_delay = true;
				}
			}
		}
		App->render->Blit(graphics, position.x + 10, position.y - 13 - r.h, &r);
	}
	if (exist_2) {
		if (movement) {
			if (shot_space) {
				if (shot_delay_2)
				{
					shot_entry_2 = SDL_GetTicks();
					shot_delay_2 = false;
				}
				shot_current_2 = SDL_GetTicks() - shot_entry;
				if (shot_current_2 > 300) {
					App->particles->AddParticle(App->particles->mirror_shoot, position.x + 5, position.y - 8, COLLIDER_PLAYER_2_SHOT);
					shot_delay_2 = true;
				}
			}
		}
		App->render->Blit(graphics, position.x + 5, position.y + 5 - r1.h, &r1);
	}
	if (exist_3) {
		if (movement) {
			if (shot_space) {
				if (shot_delay_3)
				{
					shot_entry_3 = SDL_GetTicks();
					shot_delay_3 = false;
				}
				shot_current_3 = SDL_GetTicks() - shot_entry;
				if (shot_current_3 > 300) {
					App->particles->AddParticle(App->particles->mirror_shoot, position.x + 23, position.y - 41, COLLIDER_PLAYER_2_SHOT);
					shot_delay_3 = true;
				}
			}
		}
		App->render->Blit(graphics, position.x +23, position.y - 28 - r2.h, &r2);
	}
	if (exist_4) {
		if (movement) {
			if (shot_space) {
				if (shot_delay_4)
				{
					shot_entry_4 = SDL_GetTicks();
					shot_delay_4 = false;
				}
				shot_current_4 = SDL_GetTicks() - shot_entry;
				if (shot_current_4 > 300) {
					App->particles->AddParticle(App->particles->mirror_shoot, position.x + 18, position.y + 12, COLLIDER_PLAYER_2_SHOT);
					shot_delay_4 = true;
				}
			}
		}
		App->render->Blit(graphics, position.x + 18, position.y + 25 - r3.h, &r3);
	}

	return UPDATE_CONTINUE;
}

void ModulePartner2::CheckState()
{
	//Create bool controls
	if (App->scene_select->sho_p1) {
		pressed_space = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT;
		release_space = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP;
	}
	else {
		pressed_space = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_REPEAT;
		release_space = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_UP;
	}
	//Mirror 1
	switch (state) {
	case NOT_EXISTING_2:
		movement = true;
		time_mirror = true;
		if (App->player2->power_up == 1) {
			state = SPAWN_2;
		}
		break;

	case SPAWN_2:
		if (spawn.Finished()) {
			spawn.Reset();
			state = LEVEL_ONE_2;
		}
		break;

	case LEVEL_ONE_2:
		if (App->player2->power_up == 0) {
			state = NOT_EXISTING_2;
		}
		if (pressed_space) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 300) {
				time_shoot = true;
				state = LEVEL_ONE_CHARGE_2;
				charged_fx = true;
			}
		}
		if (release_space) {
			time_shoot = true;
		}
		break;

	case LEVEL_ONE_CHARGE_2:
		if (release_space) {
			spawn.Reset();
			spawn_reverse.Reset();
			charged_shoot = true;
			state = SHOT_2;
		}
		break;

	case SHOT_2:
		if (App->player2->power_up == 0) {
			state = NOT_EXISTING_2;
		}
		if (time_mirror) {
			time_on_entry = SDL_GetTicks();
			time_mirror = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 4000) {
			state = DESPAWN;
		}
		break;

	case DESPAWN:
		if (spawn_reverse.Finished()) {
			spawn_reverse.Reset();
			charged_shoot = false;
			movement = true;
			time_mirror = true;
			state = SPAWN_2;
		}
		break;
	}

	//Mirror 2
	switch (state_2) {
	case NOT_EXISTING_2:
		time_mirror_2 = true;
		if (App->player2->power_up == 2) {
			state_2 = SPAWN_2;
		}
		break;

	case SPAWN_2:
		if (spawn2.Finished()) {
			spawn2.Reset();
			state_2 = LEVEL_ONE_2;
		}
		break;

	case LEVEL_ONE_2:
		if (App->player2->power_up <= 1) {
			state_2 = NOT_EXISTING_2;
		}
		if (pressed_space) {
			if (time_shoot_2) {
				time_on_entry_2 = SDL_GetTicks();
				time_shoot_2 = false;
			}
			current_time_2 = SDL_GetTicks() - time_on_entry_2;
			if (current_time_2 > 300) {
				time_shoot_2 = true;
				state_2 = LEVEL_ONE_CHARGE_2;
			}
		}
		if (release_space) {
			time_shoot_2 = true;
		}
		break;

	case LEVEL_ONE_CHARGE_2:
		if (release_space) {
			spawn2.Reset();
			spawn_reverse2.Reset();
			state_2 = SHOT_2;
		}
		break;

	case SHOT_2:
		if (App->player2->power_up <= 1) {
			state_2 = NOT_EXISTING_2;
		}
		if (time_mirror_2) {
			time_on_entry_2 = SDL_GetTicks();
			time_mirror_2 = false;
		}
		current_time_2 = SDL_GetTicks() - time_on_entry_2;
		if (current_time_2 > 4000) {
			state_2 = DESPAWN;
		}
		break;

	case DESPAWN:
		if (spawn_reverse2.Finished()) {
			spawn_reverse2.Reset();
			time_mirror_2 = true;
			state_2 = SPAWN_2;
		}
		break;
	}

		//Mirror 3
		switch (state_3) {
		case NOT_EXISTING_2:
			time_mirror_3 = true;
			if (App->player2->power_up == 3) {
				state_3 = SPAWN_2;
			}
			break;

		case SPAWN_2:
			if (spawn3.Finished()) {
				spawn3.Reset();
				state_3 = LEVEL_ONE_2;
			}
			break;

		case LEVEL_ONE_2:
			if (App->player2->power_up <= 2) {
				state_3 = NOT_EXISTING_2;
			}
			if (pressed_space) {
				if (time_shoot_3) {
					time_on_entry_3 = SDL_GetTicks();
					time_shoot_3 = false;
				}
				current_time_3 = SDL_GetTicks() - time_on_entry_3;
				if (current_time_3 > 300) {
					time_shoot_3 = true;
					state_3 = LEVEL_ONE_CHARGE_2;
				}
			}
			if (release_space) {
				time_shoot_3 = true;
			}
			break;

		case LEVEL_ONE_CHARGE_2:
			if (release_space) {
				spawn3.Reset();
				spawn_reverse3.Reset();
				state_3 = SHOT_2;
			}
			break;

		case SHOT_2:
			if (App->player2->power_up <= 2) {
				state_3 = NOT_EXISTING_2;
			}
			if (time_mirror_3) {
				time_on_entry_3 = SDL_GetTicks();
				time_mirror_3 = false;
			}
			current_time_3 = SDL_GetTicks() - time_on_entry_3;
			if (current_time_3 > 4000) {
				state_3 = DESPAWN;
			}
			break;

		case DESPAWN:
			if (spawn_reverse3.Finished()) {
				spawn_reverse3.Reset();
				time_mirror_3 = true;
				state_3 = SPAWN_2;
			}
			break;
		}

		//Mirror 4
		switch (state_4) {
		case NOT_EXISTING_2:
			time_mirror_4 = true;
			if (App->player2->power_up == 4) {
				state_4 = SPAWN_2;
			}
			break;

		case SPAWN_2:
			if (spawn4.Finished()) {
				spawn4.Reset();
				state_4 = LEVEL_ONE_2;
			}
			break;

		case LEVEL_ONE_2:
			if (App->player2->power_up <= 3) {
				state_4 = NOT_EXISTING_2;
			}
			if (pressed_space) {
				if (time_shoot_4) {
					time_on_entry_4 = SDL_GetTicks();
					time_shoot_4 = false;
				}
				current_time_4 = SDL_GetTicks() - time_on_entry_4;
				if (current_time_4 > 300) {
					time_shoot_4 = true;
					state_4 = LEVEL_ONE_CHARGE_2;
				}
			}
			if (release_space) {
				time_shoot_4 = true;
			}
			break;

		case LEVEL_ONE_CHARGE_2:
			if (release_space) {
				spawn4.Reset();
				spawn_reverse4.Reset();
				state_4 = SHOT_2;
			}
			break;

		case SHOT_2:
			if (App->player2->power_up <= 3) {
				state_4 = NOT_EXISTING_2;
			}
			if (time_mirror_4) {
				time_on_entry_4 = SDL_GetTicks();
				time_mirror_4 = false;
			}
			current_time_4 = SDL_GetTicks() - time_on_entry_4;
			if (current_time_4 > 4000) {
				state_4 = DESPAWN;
			}
			break;

		case DESPAWN:
			if (spawn_reverse4.Finished()) {
				spawn_reverse4.Reset();
				time_mirror_4 = true;
				state_4 = SPAWN_2;
			}
			break;
		}
}
void ModulePartner2::PerformActions()
{
	//Mirror 1
	switch (state) {
	case NOT_EXISTING_2:
		current_animation = &iddle;
		exist = false;
		break;

	case SPAWN_2:
		current_animation = &spawn;
		exist = true;
		break;

	case LEVEL_ONE_2:
		current_animation = &iddle;
		exist = true;
		break;

	case LEVEL_ONE_CHARGE_2:
		if (charged_fx) {
			App->audio->PlaySoundEffects(charged_mirror);
			charged_fx = false;
		}
		if (!spawn_reverse.Finished()) {
			current_animation = &spawn_reverse;
		}
		if (spawn_reverse.Finished() && !spawn.Finished()) {
			movement = false;
			current_animation = &spawn;
		}
		if (spawn_reverse.Finished() && spawn.Finished()) {
			current_animation = &charging;
		}
		break;

	case DESPAWN:
		current_animation = &spawn_reverse;
		break;

	case SHOT_2:
		current_animation = &iddle;
		if (shot_delay)
		{
			shot_entry = SDL_GetTicks();
			shot_delay = false;
		}
		shot_current = SDL_GetTicks() - shot_entry;
		if (shot_current > 200) {
			switch (num_bullet) {
			case 1:
				App->particles->AddParticle(App->particles->c_mirror_green, position.x + 10, position.y - 26, COLLIDER_PLAYER_2_SHOT);
				break;
			case 2:
				App->particles->AddParticle(App->particles->c_mirror_blue, position.x + 10, position.y - 26, COLLIDER_PLAYER_2_SHOT);
				break;
			case 3:
				App->particles->AddParticle(App->particles->c_mirror_cyan, position.x + 10, position.y - 26, COLLIDER_PLAYER_2_SHOT);
				num_bullet = 0;
				break;
			}
			num_bullet++;
			shot_delay = true;
		}
		break;

	}

	//Mirror 2
	switch (state_2) {
	case NOT_EXISTING_2:
		current_animation_2 = &iddle;
		exist_2 = false;
		break;

	case SPAWN_2:
		current_animation_2 = &spawn2;
		exist_2 = true;
		break;

	case LEVEL_ONE_2:
		current_animation_2 = &iddle;
		exist_2 = true;
		break;

	case LEVEL_ONE_CHARGE_2:
		if (!spawn_reverse2.Finished()) {
			current_animation_2 = &spawn_reverse2;
		}
		if (spawn_reverse2.Finished() && !spawn2.Finished()) {
			current_animation_2 = &spawn2;
		}
		if (spawn_reverse2.Finished() && spawn2.Finished()) {
			current_animation_2 = &charging;
		}
		break;

	case DESPAWN:
		current_animation_2 = &spawn_reverse2;
		break;

	case SHOT_2:
		current_animation_2 = &iddle;
		if (shot_delay_2)
		{
			shot_entry_2 = SDL_GetTicks();
			shot_delay_2 = false;
		}
		shot_current_2 = SDL_GetTicks() - shot_entry_2;
		if (shot_current_2 > 200) {
			switch (num_bullet_2) {
			case 1:
				App->particles->AddParticle(App->particles->c_mirror_green, position.x + 5, position.y - 8, COLLIDER_PLAYER_2_SHOT);
				break;
			case 2:
				App->particles->AddParticle(App->particles->c_mirror_blue, position.x + 5, position.y - 8, COLLIDER_PLAYER_2_SHOT);
				break;
			case 3:
				App->particles->AddParticle(App->particles->c_mirror_cyan, position.x + 5, position.y - 8, COLLIDER_PLAYER_2_SHOT);
				num_bullet_2 = 0;
				break;
			}
			num_bullet_2++;
			shot_delay_2 = true;
		}
		break;
	}

	//Mirror 3
	switch (state_3) {
	case NOT_EXISTING_2:
		current_animation_3 = &iddle;
		exist_3 = false;
		break;

	case SPAWN_2:
		current_animation_3 = &spawn3;
		exist_3 = true;
		break;

	case LEVEL_ONE_2:
		current_animation_3 = &iddle;
		exist_3 = true;
		break;

	case LEVEL_ONE_CHARGE_2:
		if (!spawn_reverse3.Finished()) {
			current_animation_3 = &spawn_reverse3;
		}
		if (spawn_reverse3.Finished() && !spawn3.Finished()) {
			current_animation_3 = &spawn3;
		}
		if (spawn_reverse3.Finished() && spawn3.Finished()) {
			current_animation_3 = &charging;
		}
		break;

	case DESPAWN:
		current_animation_3 = &spawn_reverse3;
		break;

	case SHOT_2:
		current_animation_3 = &iddle;
		if (shot_delay_3)
		{
			shot_entry_3 = SDL_GetTicks();
			shot_delay_3 = false;
		}
		shot_current_3 = SDL_GetTicks() - shot_entry_3;
		if (shot_current_3 > 200) {
			switch (num_bullet_3) {
			case 1:
				App->particles->AddParticle(App->particles->c_mirror_green, position.x + 23, position.y - 41, COLLIDER_PLAYER_2_SHOT);
				break;
			case 2:
				App->particles->AddParticle(App->particles->c_mirror_blue, position.x + 23, position.y - 41, COLLIDER_PLAYER_2_SHOT);
				break;
			case 3:
				App->particles->AddParticle(App->particles->c_mirror_cyan, position.x + 23, position.y - 41, COLLIDER_PLAYER_2_SHOT);
				num_bullet_3 = 0;
				break;
			}
			num_bullet_3++;
			shot_delay_3 = true;
		}
		break;
	}


	//Mirror 4
	switch (state_4) {
	case NOT_EXISTING_2:
		current_animation_4 = &iddle;
		exist_4 = false;
		break;

	case SPAWN_2:
		current_animation_4 = &spawn4;
		exist_4 = true;
		break;

	case LEVEL_ONE_2:
		current_animation_4 = &iddle;
		exist_4 = true;
		break;

	case LEVEL_ONE_CHARGE_2:
		if (!spawn_reverse4.Finished()) {
			current_animation_4 = &spawn_reverse4;
		}
		if (spawn_reverse4.Finished() && !spawn4.Finished()) {
			current_animation_4 = &spawn4;
		}
		if (spawn_reverse4.Finished() && spawn4.Finished()) {
			current_animation_4 = &charging;
		}
		break;

	case DESPAWN:
		current_animation_4 = &spawn_reverse4;
		break;

	case SHOT_2:
		current_animation_4 = &iddle;
		if (shot_delay_4)
		{
			shot_entry_4 = SDL_GetTicks();
			shot_delay_4 = false;
		}
		shot_current_4 = SDL_GetTicks() - shot_entry_4;
		if (shot_current_4 > 200) {
			switch (num_bullet_4) {
			case 1:
				App->particles->AddParticle(App->particles->c_mirror_green, position.x + 18, position.y + 12, COLLIDER_PLAYER_2_SHOT);
				break;
			case 2:
				App->particles->AddParticle(App->particles->c_mirror_blue, position.x + 18, position.y + 12, COLLIDER_PLAYER_2_SHOT);
				break;
			case 3:
				App->particles->AddParticle(App->particles->c_mirror_cyan, position.x + 18, position.y + 12, COLLIDER_PLAYER_2_SHOT);
				num_bullet_4 = 0;
				break;
			}
			num_bullet_4++;
			shot_delay_4 = true;
		}
		break;
	}
}
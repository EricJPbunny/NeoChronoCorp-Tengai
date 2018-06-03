#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSelect.h"
#include "ModuleSceneAir.h"
#include "ModulePlayer3.h"
#include "ModulePartner3.h"
#include "ModuleUI.h"


#include "SDL\include\SDL_timer.h"

ModulePartner3::ModulePartner3()
{
	graphics = nullptr;
	current_animation = nullptr;

	spawn.PushBack({ 14,212,5,3 });
	spawn.PushBack({ 45,210,12,6 });
	spawn.PushBack({ 80,210,19,8 });
	spawn.PushBack({ 126,209,23,10 });
	spawn.speed = 0.15f;


	spawn_reverse.PushBack({ 126,209,23,10 });
	spawn_reverse.PushBack({ 80,210,19,8 });
	spawn_reverse.PushBack({ 45,210,12,6 });
	spawn_reverse.PushBack({ 14,212,5,3 });
	spawn_reverse.speed = 0.30f;


	iddle.PushBack({ 411,206,31,13 });
	iddle.PushBack({ 372,203,30,14 });
	iddle.PushBack({ 455,205,30,13 });
	iddle.PushBack({ 337,203,27,14 });
	iddle.speed = 0.15f;

	
	charging.PushBack({ 282,199,28,21 });
	charging.PushBack({ 247,198,24,21 });
	charging.PushBack({ 208,197,27,21 });
	charging.PushBack({ 168,200,27,21 });
	charging.speed = 0.10f;


	pre_shot.PushBack({ 9,4,48,42 });
	pre_shot.PushBack({ 74,4,53,46 });
	pre_shot.PushBack({ 147,5,58,52 });
	pre_shot.PushBack({ 222,7,58,53 });
	pre_shot.PushBack({ 289,6,64,57 });
	pre_shot.PushBack({ 377,8,64,58 });
	pre_shot.speed = 0.15f;


	shot.PushBack({ 10,72,76,37 });
	shot.PushBack({ 94,74,76,38 });
	shot.PushBack({ 192,76,79,38 });
	shot.PushBack({ 287,82,79,37 });
	shot.PushBack({ 389,79,79,38 });
	shot.PushBack({ 13,135,79,37 });
	shot.PushBack({ 107,136,76,37 });
	shot.PushBack({ 198,137,76,38 });
	shot.speed = 0.15f;


	decharging.PushBack({8,296,74,42});
	decharging.PushBack({92,300,68,39});
	decharging.PushBack({169,302,63,36});
	decharging.PushBack({243,303,59,33});
	decharging.PushBack({311,304,54,31});
	decharging.PushBack({372,305,50,28});
	decharging.PushBack({429,305,45,25});
	decharging.PushBack({14,346,40,23});
	decharging.speed = 0.15;


}

ModulePartner3::~ModulePartner3()
{
	//destroyer
}

bool ModulePartner3::Start()
{
	LOG("Loading partner textures");
	graphics = App->textures->Load("assets/sprite/Socrates_Spritesheet.png");
	if (graphics == nullptr)
	{
		LOG("Could not load partner textures")
			return false;
	}

	position.x = App->player3->position.x;
	position.y = App->player3->position.y;
	return true;
}

bool ModulePartner3::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(graphics);
	graphics = nullptr;
	if (graphics != nullptr)
	{
		LOG("Could not unload partner textures")
			return false;
	}

	return true;
}


update_status ModulePartner3::Update()
{
	if (!App->scene_select->sho_p1) {
		shot_space_3 = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->controller_A_button == KEY_STATE::KEY_DOWN;
	}
	else {
		shot_space_3 = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN || App->input->controller_A_button2 == KEY_STATE::KEY_DOWN;
	}
	CheckState();

	PerformActions();

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN) {
		App->player3->power_up++;
	}
	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN) {
		App->player3->power_up--;
	}

	//Draw partner
	SDL_Rect r = current_animation->GetCurrentFrame();

	//shuriken shot with 1st power up
	if (App->player3->power_up==1) {
		if (movement) {
			if (shot_space_3) {
				if (shot_delay)
				{
					shot_entry = SDL_GetTicks();
					shot_delay = false;
				}
				shot_current = SDL_GetTicks() - shot_entry;
				if (shot_current > 300) {
					multiple_shot = true;
					LOG("Este si peaso weabo");
					App->particles->AddParticle(App->particles->shuriken_socrates_1, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_2, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					shot_delay = true;
				}
			}
			if (multiple_shot) 
			{
				increaser++;
				if (increaser > 10) {
					LOG("Entro el primero weh");
					App->particles->AddParticle(App->particles->shuriken_socrates_1, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_2, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					multiple_shot = false;
					multiple_shot_2 = true;
					increaser = 0;
				}
				
			}
			if (multiple_shot_2)
			{
				increaser++;
				if (increaser > 10) {
					LOG("Entro entro entro MRajoy");
					App->particles->AddParticle(App->particles->shuriken_socrates_1, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_2, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					multiple_shot_2 = false;
					increaser = 0;
				}

			}
		}
		App->render->Blit(graphics, position.x + 5, position.y - 17 - r.h, &r);
	}
	//shuriken shot with 2nd power up
	if (App->player3->power_up == 2) {
		if (movement) {
			if (shot_space_3) {
				if (shot_delay)
				{
					shot_entry = SDL_GetTicks();
					shot_delay = false;
				}
				shot_current = SDL_GetTicks() - shot_entry;
				if (shot_current > 300) {
					multiple_shot = true;
					App->particles->AddParticle(App->particles->shuriken_socrates_3, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_4, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					shot_delay = true;
				}
			}
			if (multiple_shot) 
			{
				increaser++;
				if (increaser > 15) 
				{
					App->particles->AddParticle(App->particles->shuriken_socrates_3, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_4, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					multiple_shot = false;
					multiple_shot_2 = true;
					increaser = 0;
				}
				
			}
			if (multiple_shot_2)
			{
				increaser++;
				if (increaser > 10) {
					LOG("Entro entro entro MRajoy");
					App->particles->AddParticle(App->particles->shuriken_socrates_3, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_4, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					multiple_shot_2 = false;
					increaser = 0;
				}

			}
		}
		App->render->Blit(graphics, position.x + 5, position.y - 17 - r.h, &r);
	}
	//shuriken shot with 3rd power up
	if (App->player3->power_up == 3) {
		if (movement) {
			if (shot_space_3) {
				if (shot_delay)
				{
					shot_entry = SDL_GetTicks();
					shot_delay = false;
				}
				shot_current = SDL_GetTicks() - shot_entry;
				if (shot_current > 300) {
					multiple_shot = true;
					App->particles->AddParticle(App->particles->shuriken_socrates_5, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_6, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					shot_delay = true;
				}
			}
			if (multiple_shot) {
				increaser++;
				if (increaser > 10) {
					App->particles->AddParticle(App->particles->shuriken_socrates_5, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_6, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					multiple_shot = false;
					multiple_shot_2 = true;
					increaser = 0;
				}
			}
			if (multiple_shot_2)
			{
				increaser++;
				if (increaser > 10) {
					LOG("Entro entro entro MRajoy");
					App->particles->AddParticle(App->particles->shuriken_socrates_5, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_6, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					multiple_shot_2 = false;
					increaser = 0;
				}

			}
		}
		App->render->Blit(graphics, position.x + 5, position.y - 17 - r.h, &r);
	}
	//shuriken shot with 4th power up
	if (App->player3->power_up == 4) {
		if (movement) {
			if (shot_space_3) {
				if (shot_delay)
				{
					shot_entry = SDL_GetTicks();
					shot_delay = false;
				}
				shot_current = SDL_GetTicks() - shot_entry;
				if (shot_current > 300) {
					multiple_shot = true;
					App->particles->AddParticle(App->particles->shuriken_socrates_5, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_6, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_7, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_8, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					shot_delay = true;
				}
			}
			if (multiple_shot) {
				increaser++;
				if (increaser > 10) {
					App->particles->AddParticle(App->particles->shuriken_socrates_5, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_6, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_7, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_8, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					multiple_shot = false;
					multiple_shot_2 = true;
					increaser = 0;
				}
			}
			if (multiple_shot_2)
			{
				increaser++;
				if (increaser > 10) {
					LOG("Entro entro entro MRajoy");
					App->particles->AddParticle(App->particles->shuriken_socrates_5, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_6, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_7, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					App->particles->AddParticle(App->particles->shuriken_socrates_8, position.x + 23, position.y - 30, COLLIDER_PLAYER_3_SHOT);
					multiple_shot_2 = false;
					increaser = 0;
				}

			}
		}
		App->render->Blit(graphics, position.x + 5, position.y - 17 - r.h, &r);
	}

	//Set Position
	if (movement) {
		position.x = App->player3->position.x - 25;
		position.y = App->player3->position.y - 10;
	}
	if (!movement && !charged_shoot) {
		position.x = App->player3->position.x + 25;
		position.y = App->player3->position.y - 20;
	}
	else if (charged_shoot) {
		position.x += App->scene_air->speed / SCREEN_SIZE;
	}

	return update_status::UPDATE_CONTINUE;
}


void ModulePartner3::CheckState()
{
	//Create bool controls
	if (!App->scene_select->sho_p1) {
		pressed_space_3 = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT;
		release_space_3 = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP;
	}
	else {
		pressed_space_3 = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_REPEAT;
		release_space_3 = App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_UP;
	}


	switch (state)
	{

	case NOT_EXISTING_3:
		movement = true;
		time_socrates = true;
		if (App->player3->power_up == 1) 
		{
			state = SPAWN_3;
		}
		break;

	case SPAWN_3:
		if (spawn.Finished()) {
			spawn.Reset();
			state = IDLE_SOCRATES;
		}
		break;

	case IDLE_SOCRATES:
		if (App->player3->power_up == 0) 
		{
			state = NOT_EXISTING_3;
		}

		//make it charge
		if (pressed_space_3) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 300) {
				time_shoot = true;
				state = CHARGING;
			}
		}
		if (release_space_3) {
			time_shoot = true;
		}
		break;

	case CHARGING:
		//make it shot fire while pressing a key
		if (release_space_3) {
			spawn.Reset();
			spawn_reverse.Reset();
			charged_shoot = true;
			state = FIRE_3;
		}
		break;


	case FIRE_3:
		if (App->player3->power_up == 0) {
			state = NOT_EXISTING_3;
		}

		if (time_socrates) {
			time_on_entry = SDL_GetTicks();
			time_socrates = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 4000) {
			state = DECHARGING;
		}
		break;


	case DECHARGING:
		if (App->player3->power_up == 0) {
			state = NOT_EXISTING_3;
		}
		if (decharging.Finished()) {
			decharging.Reset();
			state = DESPAWN_3;
		}
		charged_shoot = true;
		break;

	case DESPAWN_3:
		if (spawn_reverse.Finished()) {
			spawn_reverse.Reset();
			charged_shoot = false;
			movement = true;
			time_socrates = true;
			state = SPAWN_3;
		}
		break;
	}
}


void ModulePartner3::PerformActions()
{
	switch (state) {
	case NOT_EXISTING_3:
		current_animation = &iddle;
		exist = false;
		break;

	case SPAWN_3:
		current_animation = &spawn;
		exist = true;
		break;

	case IDLE_SOCRATES:
		current_animation = &iddle;
		exist = true;
		break;

	case CHARGING:
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


	case FIRE_3:
		current_animation = &pre_shot;
		if (pre_shot.Finished()) {
			current_animation = &shot;
			if (shot_delay)
			{
				shot_entry = SDL_GetTicks();
				shot_delay = false;
			}
			shot_current = SDL_GetTicks() - shot_entry;
			if (shot_current > 200) {

				App->particles->AddParticle(App->particles->fire, position.x + 77, position.y - 55, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire2, position.x + 84, position.y - 55, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire3, position.x + 95, position.y - 55, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire4, position.x + 100, position.y - 65, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire5, position.x + 108, position.y - 65, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire6, position.x + 113, position.y - 65, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire7, position.x + 115, position.y - 65, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire8, position.x + 123, position.y - 65, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire9, position.x + 129, position.y - 65, COLLIDER_PLAYER_3_SHOT);
				App->particles->AddParticle(App->particles->fire10, position.x + 133, position.y - 65, COLLIDER_PLAYER_3_SHOT);
				shot_delay = true;
			}
			
		}
		break;


	case DECHARGING:
		current_animation = &decharging;
		break;


	case DESPAWN_3:
		current_animation = &spawn_reverse;
		break;


	}
}
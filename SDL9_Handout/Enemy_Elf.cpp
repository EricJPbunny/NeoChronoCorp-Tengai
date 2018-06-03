#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "Enemy_Elf.h"
#include "SDL\include\SDL_timer.h"

Enemy_Elf::Enemy_Elf(int x, int y, int type) :Enemy(x, y, type)
{
	fire_rate = 90;
	boss_sprite = App->textures->Load("assets/sprite/Tijeras_Boss.png");

	previous.PushBack({ 42, 736, 32, 35 });
	previous.PushBack({ 80, 736, 32, 35 });
	previous.PushBack({ 121, 736, 32, 35 });
	previous.PushBack({ 165, 736, 32, 35 });
	previous.PushBack({ 207, 736, 32, 35 });
	previous.speed = 0.08f;

	spawn.PushBack({ 18, 305, 104, 89 });
	spawn.PushBack({ 154, 305, 104, 89 });
	spawn.PushBack({ 289, 305, 104, 89 });
	spawn.PushBack({ 435, 305, 104, 89 });
	spawn.speed = 0.1f;


	stay.PushBack({ 1637, 19, 75, 89});
	stay.speed = 0.09f;
	stay2.PushBack({ 1553, 19, 42, 87});
	stay2.speed = 0.09f;

	idle.PushBack({ 1439, 20, 83, 79 });
	idle.PushBack({ 1228, 20, 83 ,79 });
	idle.PushBack({ 1328, 20, 83, 79 });
	idle.PushBack({ 642, 20, 83, 79 });
	idle.PushBack({ 224, 20, 83, 79 });
	idle.PushBack({ 423, 20, 83, 79 });
	idle.PushBack({ 1226, 20, 83, 79 });
    idle.speed = 0.1f;

	back.PushBack({ 1229, 28, 81, 71 });
	back.speed = 0.1f;

	back2.PushBack({ 1330, 28, 81, 71 });
	back2.speed = 0.1f;

	back3.PushBack({ 1224, 28, 81, 71 });
	back3.speed = 0.1f;
	
	back4.PushBack({ 119, 25, 83, 69 });
	back4.speed = 0.1f;


	hand.PushBack({ 777, 25, 97, 72 });
	hand.speed = 0.1f;
	hand2.PushBack({ 894, 25, 97, 72 });
	hand2.speed = 0.1f;
	hand3.PushBack({ 524, 26, 80, 69 });
	hand3.speed = 0.1f;
	
	movement.PushBack({ 1.0f, 0.0f },15, &previous);
	movement.PushBack({ 1.0f, 0.0f }, 150, &spawn);
	movement.PushBack({ 1.0f, 0.0f },10, &stay);
	movement.PushBack({ 1.0f, 0.0f },10, &stay2);
	movement.PushBack({ 1.0f, 0.0f }, 20, &idle);
	movement.PushBack({ 1.5f, 0.0f }, 30, &idle);
	movement.PushBack({ 1.5f, 0.0f }, 10, &back);
	movement.PushBack({ 1.5f, 0.0f }, 10, &back2);
	movement.PushBack({ 1.5f, 0.0f }, 10, &back3);
	movement.PushBack({ 1.5f, 0.0f }, 10, &back4);
	movement.PushBack({ 1.0f, 0.0f }, 20, &hand);
	movement.PushBack({ 1.0f, 0.0f }, 150, &hand2);
	movement.PushBack({ 1.0f, 0.0f }, 20, &hand);
	movement.PushBack({ 1.0f, 0.0f }, 10, &hand3);
	movement.PushBack({ -1.5f, 0.0f }, 20, &hand3);
	movement.PushBack({ 1.0f, 0.0f }, 20, &idle);
	movement.PushBack({ 1.0f, 0.0f }, 10, &stay2);
	movement.PushBack({ 1.0f, 0.0f }, 10, &stay);
	movement.PushBack({ 1.0f, 0.0f }, 150, &spawn);
	movement.PushBack({ 1.0f, 0.0f }, 10, &stay);
	movement.PushBack({ 1.0f, 0.0f }, 10, &stay2);
	movement.PushBack({ 1.0f, 0.0f }, 20, &idle);
	movement.PushBack({ 1.0f, 0.0f }, 20, &hand);
	movement.PushBack({ 1.0f, 0.0f }, 150, &hand2);
	movement.PushBack({ 1.0f, 0.0f }, 20, &hand);
	movement.PushBack({ 1.0f, 0.0f }, 10, &hand3);
	movement.PushBack({ 1.0f, 0.0f }, 20, &idle);
	movement.PushBack({ 1.0f, 0.0f }, 10, &stay2);
	movement.PushBack({ 1.0f, 0.0f }, 10, &stay);
	movement.PushBack({ 1.0f, 0.0f }, 150, &spawn);
	movement.PushBack({ 1.0f, 0.0f }, 10, &stay);
	movement.PushBack({ 1.0f, 0.0f }, 10, &stay2);
	movement.PushBack({ 1.0f, 0.0f }, 20, &idle);
	movement.PushBack({ 1.0f, 0.0f }, 20, &hand);
	movement.PushBack({ 1.0f, 0.0f }, 150, &hand2);
	movement.PushBack({ 1.0f, 0.0f }, 20, &hand);
	movement.PushBack({ 1.0f, 0.0f }, 10, &hand3);




	
	
	animation = &previous;
    this->type = type;
	collider = App->collision->AddCollider({ 0, 0, 30, 50 }, COLLIDER_TYPE::COLLIDER_ELF, (Module*)App->enemies);
	originalposition.y = y;
	originalposition.x = x;

}


Enemy_Elf::~Enemy_Elf()
{
	App->textures->Unload(boss_sprite);

}


void Enemy_Elf::Move()
{

	if (timer) {
		time_on_entry = SDL_GetTicks();
		timer = false;
	}
	current_time = SDL_GetTicks() - time_on_entry;

	if (current_time > 5800 && shooting) {

		App->particles->AddParticle(App->particles->archer_shoot, position.x, position.y+15, COLLIDER_ENEMY_SHOT);
		shooting = false;

	}
	if (current_time > 9000 && shurikens ) {
	
			App->particles->AddParticle(App->particles->elf_shuriken, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->elf_shuriken2, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

			App->particles->AddParticle(App->particles->elf_shuriken3, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->elf_shuriken4, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

			App->particles->AddParticle(App->particles->elf_shuriken5, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->elf_shuriken6, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

			App->particles->AddParticle(App->particles->elf_shuriken7, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->elf_shuriken8, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

			App->particles->AddParticle(App->particles->elf_shuriken9, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->elf_shuriken10, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);

			App->particles->AddParticle(App->particles->elf_shuriken11, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->elf_shuriken12, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

			App->particles->AddParticle(App->particles->elf_shuriken13, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->elf_shuriken14, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

			App->particles->AddParticle(App->particles->elf_shuriken15, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->elf_shuriken16, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
			shurikens = false;
		

	}
	if (current_time > 9800 && shurikens2) {

		App->particles->AddParticle(App->particles->elf_shuriken, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken2, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken3, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken4, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken5, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken6, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken7, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken8, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken9, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken10, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken11, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken12, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken13, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken14, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken15, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken16, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		shurikens2 = false;

	}
	if (current_time > 10600 && shurikens3) {

		App->particles->AddParticle(App->particles->elf_shuriken, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken2, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken3, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken4, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken5, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken6, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken7, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken8, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken9, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken10, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken11, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken12, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken13, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken14, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken15, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken16, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
		shurikens3 = false;


	}

	if (current_time > 11400 && shurikens4) {

		App->particles->AddParticle(App->particles->elf_shuriken, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken2, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken3, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken4, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken5, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken6, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken7, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken8, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken9, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken10, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken11, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken12, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken13, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken14, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken15, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken16, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
		shurikens4 = false;


	}

	if (current_time > 13500 && shooting2) {

		App->particles->AddParticle(App->particles->elf_shoot, position.x, position.y , COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shoot2, position.x+5, position.y , COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shoot3, position.x, position.y , COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shoot4, position.x+5, position.y , COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shoot5, position.x, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shoot6, position.x + 5, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shoot7, position.x , position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shoot8, position.x +5, position.y, COLLIDER_ENEMY_SHOT);
		shooting2 = false;

	}

	if (current_time > 17300 && shurikens5) {

		App->particles->AddParticle(App->particles->elf_shuriken, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken2, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken3, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken4, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken5, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken6, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken7, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken8, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken9, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken10, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken11, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken12, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken13, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken14, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken15, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken16, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		shurikens5 = false;

	}

	if (current_time > 18100 && shurikens6) {

		App->particles->AddParticle(App->particles->elf_shuriken, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken2, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken3, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken4, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken5, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken6, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken7, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken8, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken9, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken10, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken11, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken12, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken13, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken14, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken15, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken16, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		shurikens6 = false;

	}

	if (current_time > 18900 && shurikens7) {

		App->particles->AddParticle(App->particles->elf_shuriken, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken2, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken3, position.x + 60, position.y + 10, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken4, position.x + 60, position.y - 10, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken5, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken6, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken7, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken8, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken9, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken10, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken11, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken12, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken13, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken14, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->elf_shuriken15, position.x + 60, position.y, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->elf_shuriken16, position.x + 40, position.y, COLLIDER_ENEMY_SHOT);

		shurikens7 = false;

	}


	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed(&animation);
	}

	collider->SetPos(position.x + 90, position.y + 60);
	
}



void Enemy_Elf::Draw(SDL_Texture* sprites) {
	Enemy::Draw(boss_sprite);
}
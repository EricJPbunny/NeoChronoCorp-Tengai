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




	animation = &previous;
	
	originalposition.y = y;
	originalposition.x = x;
//	this->type = type;
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


	if (current_time > 3000 && shooting) {

		App->particles->AddParticle(App->particles->bird_shoot2, position.x, position.y + 15);
		App->particles->AddParticle(App->particles->bird_shoot, position.x, position.y + 15);
		timer = true;
		shooting = true;

	}

	if (App->ui->enemies_movement) {
		position = originalposition + movement.GetCurrentSpeed(&animation);
	}
}

	/*if (previous.Finished())
	{
		animation = &spawn;
	}
	if (spawn.Finished())
	{
		animation = &stay;
	}
	if (stay.Finished())
	{
		animation = &stay2;
	}
	if (stay2.Finished())
	{
		animation = &idle;
	}
	if (idle.Finished())
	{
		animation = &back;
	}
	if (back.Finished())
	{
		animation = &back2;
	}
	if (back2.Finished())
	{
		animation = &back3;
	}
	if (back3.Finished())
	{
		animation = &back4;
	}
	if (back4.Finished())
	{
		animation = &hand;
	}
	if (hand.Finished())
	{
		animation = &hand2;
	}

}*/

void Enemy_Elf::Draw(SDL_Texture* sprites) {
	Enemy::Draw(boss_sprite);
}
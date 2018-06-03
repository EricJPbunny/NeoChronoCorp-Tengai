#include "Application.h"
#include "Enemy_Bird.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL_timer.h"


Enemy_Bird::Enemy_Bird(int x, int y, int type) :Enemy(x, y, type)
{
	idle.PushBack({ 11,90,40,37 });
	idle.PushBack({ 55,88,40,37 });
	idle.speed = 0.2f;

	shot.PushBack({ 100,87,40,37 });
	shot.speed = 0.2f;
	shot2.PushBack({ 151,84,40,37 });
	shot2.speed = 0.2f;
	shot3.PushBack({ 201,82,40,37 });
	shot3.speed = 0.2f;
	shot4.PushBack({ 248,80,40,37 });
	shot4.speed = 0.2f;
	shot5.PushBack({ 290,79,40,37 });
	shot5.speed = 0.2f;
	shot6.PushBack({ 336,80,40,37 });
	shot6.speed = 0.2f;


	main.PushBack({ 377,80,40,37 });
	main.speed = 0.2f;


	birdup.PushBack({ -0.4f, 0.0f }, 150, &idle);
	birdup.PushBack({ 1.0f, 0.0f }, 3, &shot);
	birdup.PushBack({ 1.0f, 0.0f }, 3, &shot2);
	birdup.PushBack({ 1.0f, 0.0f }, 3, &shot3);
	birdup.PushBack({ 1.0f, 0.0f }, 3, &shot4);
	birdup.PushBack({ 1.0f, 0.0f }, 3, &shot5);
	birdup.PushBack({ 1.0f, 0.0f }, 3, &shot6);
	birdup.PushBack({ 1.0f, 0.0f }, 50, &main);
	birdup.PushBack({ 0.2f, 1.0f }, 300, &idle);


	birddown.PushBack({ -0.4f, 0.0f }, 150, &idle);
	birddown.PushBack({ 1.0f, 0.0f }, 3, &shot);
	birddown.PushBack({ 1.0f, 0.0f }, 3, &shot2);
	birddown.PushBack({ 1.0f, 0.0f }, 3, &shot3);
	birddown.PushBack({ 1.0f, 0.0f }, 3, &shot4);
	birddown.PushBack({ 1.0f, 0.0f }, 3, &shot5);
	birddown.PushBack({ 1.0f, 0.0f }, 3, &shot6);
	birddown.PushBack({ 1.0f, 0.0f }, 50, &main);
	birddown.PushBack({ 0.2f, -1.0f }, 200, &idle);

	birdmov.PushBack({ -0.4f, -0.4f }, 150, &idle);
	birdmov.PushBack({ 1.0f, -0.5f }, 3, &shot);
	birdmov.PushBack({ 1.0f, -0.5f }, 3, &shot2);
	birdmov.PushBack({ 1.0f, -0.5f }, 3, &shot3);
	birdmov.PushBack({ 1.0f, -0.5f }, 3, &shot4);
	birdmov.PushBack({ 1.0f, -0.5f }, 3, &shot5);
	birdmov.PushBack({ 1.0f, -0.5f }, 3, &shot6);
	birdmov.PushBack({ 1.0f, -0.5f }, 50, &main);
	birdmov.PushBack({ -0.4f, -0.4f }, 200, &idle);

	this->type = type;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Bird::Move()
{
	if (timer) {
		time_on_entry = SDL_GetTicks();
		timer = false;
	}
	current_time = SDL_GetTicks() - time_on_entry;


	if (current_time > 3000 && shooting ) {

		App->particles->AddParticle(App->particles->bird_shoot2, position.x, position.y + 15, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->bird_shoot, position.x, position.y + 15, COLLIDER_ENEMY_SHOT);
		timer = true;
		shooting = false;
	
		
}

	if (type == 1) {
		if (App->ui->enemies_movement) {
			position = originalposition + birdup.GetCurrentSpeed(&animation);
		}
	}
	if (type == 2) {
		if (App->ui->enemies_movement) {
			position = originalposition + birddown.GetCurrentSpeed(&animation);
		}
	}
	if (type == 3) {
		if (App->ui->enemies_movement) {
			position = originalposition + birdmov.GetCurrentSpeed(&animation);
		}
	}


}


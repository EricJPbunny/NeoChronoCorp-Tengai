#include "Application.h"
#include "Enemy_Knife.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL_timer.h"


Enemy_Knife::Enemy_Knife(int x, int y, int type) :Enemy(x, y, type)
{
	idle.PushBack({ 6,50,32,30 });
	idle.PushBack({ 50,49,32,30 });
	idle.PushBack({ 91,49,32,30 });
	idle.PushBack({ 135,49,32,30 });
	idle.PushBack({ 182,50,32,30 });
	idle.PushBack({ 229,49,32,30 });
	idle.PushBack({ 274,48,32,30 });
	idle.PushBack({ 325,49,32,30 });
	idle.speed = 0.2f;

	movement.PushBack({ -0.5f, 0.0f }, 150, &idle);
	movement.PushBack({ 0.0f, 0.0f }, 140, &idle);
	movement.PushBack({ -1.2f, 0.0f }, 1050, &idle);

    diagonal.PushBack({ -0.8f, 0.7f }, 860, &idle);
	diagonal.PushBack({ -0.8f, -0.7f }, 60, &idle);
	

	diagonalup.PushBack({ -0.8f, -0.7f }, 860, &idle);
	diagonalup.PushBack({ -0.8f, 0.7f }, 60, &idle);

	updown.PushBack({ -0.8f, -0.7f }, 60, &idle);
	updown.PushBack({ -0.8f, 0.7f }, 60, &idle);



	this->type = type;
	

	collider = App->collision->AddCollider({ 0, 0, 40, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Enemy_Knife::Move()
{
	if (timer) {
		time_on_entry = SDL_GetTicks();
		timer = false;
	}
	current_time = SDL_GetTicks() - time_on_entry;
	if (current_time > 1000 && shooting) {
		App->particles->AddParticle(App->particles->enemie_shoot, position.x, position.y+6, COLLIDER_ENEMY_SHOT);
		timer = true;
		shooting = false;
	}


	if (type == 1) {
		if (App->ui->enemies_movement) {
			position = originalposition + movement.GetCurrentSpeed(&animation);
		}
	}
	if (type == 2) {
		if (App->ui->enemies_movement) {
			position = originalposition + diagonal.GetCurrentSpeed(&animation);
		}
	}
	if (type == 3) {
		if (App->ui->enemies_movement) {
			position = originalposition + diagonalup.GetCurrentSpeed(&animation);
		}
	}
	if (type == 4) {
		if (App->ui->enemies_movement) {
			position = originalposition + updown.GetCurrentSpeed(&animation);
		}
	}
}

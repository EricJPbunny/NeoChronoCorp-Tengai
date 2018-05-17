#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_REDOVNI] = false;
	matrix[COLLIDER_WALL][COLLIDER_NINJA] = false;
	matrix[COLLIDER_WALL][COLLIDER_HITBOX] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_WALL][COLLIDER_COIN] = true;
	matrix[COLLIDER_WALL][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_REDOVNI] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_NINJA] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HITBOX] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_COIN] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_REDOVNI] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_NINJA] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HITBOX] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_3_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_COIN] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_TRIGGER] = true;

	matrix[COLLIDER_REDOVNI][COLLIDER_WALL] = false;
	matrix[COLLIDER_REDOVNI][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_REDOVNI][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_REDOVNI][COLLIDER_REDOVNI] = false;
	matrix[COLLIDER_REDOVNI][COLLIDER_NINJA] = false;
	matrix[COLLIDER_REDOVNI][COLLIDER_HITBOX] = true;
	matrix[COLLIDER_REDOVNI][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_REDOVNI][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_REDOVNI][COLLIDER_PLAYER_3_SHOT] = true;
	matrix[COLLIDER_REDOVNI][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_REDOVNI][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_REDOVNI][COLLIDER_COIN] = false;
	matrix[COLLIDER_REDOVNI][COLLIDER_TRIGGER] = true;

	matrix[COLLIDER_NINJA][COLLIDER_WALL] = false;
	matrix[COLLIDER_NINJA][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_NINJA][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_NINJA][COLLIDER_REDOVNI] = false;
	matrix[COLLIDER_NINJA][COLLIDER_NINJA] = false;
	matrix[COLLIDER_NINJA][COLLIDER_HITBOX] = true;
	matrix[COLLIDER_NINJA][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_NINJA][COLLIDER_PLAYER_2_SHOT] = true;
	matrix[COLLIDER_NINJA][COLLIDER_PLAYER_3_SHOT] = true;
	matrix[COLLIDER_NINJA][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_NINJA][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_NINJA][COLLIDER_COIN] = false;
	matrix[COLLIDER_NINJA][COLLIDER_TRIGGER] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_REDOVNI] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_NINJA] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_HITBOX] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_REDOVNI] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_NINJA] = true;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_HITBOX] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_PLAYER_2_SHOT][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_REDOVNI] = true;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_NINJA] = true;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_HITBOX] = false;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_PLAYER_3_SHOT][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_HITBOX][COLLIDER_WALL] = false;
	matrix[COLLIDER_HITBOX][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_HITBOX][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_HITBOX][COLLIDER_REDOVNI] = true;
	matrix[COLLIDER_HITBOX][COLLIDER_NINJA] = true;
	matrix[COLLIDER_HITBOX][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_HITBOX][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_HITBOX][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_HITBOX][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_HITBOX][COLLIDER_HITBOX] = false;
	matrix[COLLIDER_HITBOX][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_HITBOX][COLLIDER_COIN] = false;
	matrix[COLLIDER_HITBOX][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_REDOVNI] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_NINJA] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HITBOX] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_COIN] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_POWER_UP][COLLIDER_WALL] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_REDOVNI] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_NINJA] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_HITBOX] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_COIN] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_COIN][COLLIDER_WALL] = true;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_COIN][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_COIN][COLLIDER_REDOVNI] = false;
	matrix[COLLIDER_COIN][COLLIDER_NINJA] = false;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_HITBOX] = true;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_COIN][COLLIDER_COIN] = false;
	matrix[COLLIDER_COIN][COLLIDER_TRIGGER] = false;

	matrix[COLLIDER_TRIGGER][COLLIDER_WALL] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_TRIGGER][COLLIDER_REDOVNI] = true;
	matrix[COLLIDER_TRIGGER][COLLIDER_NINJA] = true;
	matrix[COLLIDER_TRIGGER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_HITBOX] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_PLAYER_2_SHOT] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_PLAYER_3_SHOT] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_COIN] = false;
	matrix[COLLIDER_TRIGGER][COLLIDER_TRIGGER] = false;

}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Test all collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;

		case COLLIDER_NINJA: // green/bue
			App->render->DrawQuad(colliders[i]->rect, 0, 204, 153, alpha);
			break;

		case COLLIDER_REDOVNI: // dark purple
			App->render->DrawQuad(colliders[i]->rect, 51, 0, 51, alpha);
			break;

		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER_2_SHOT: //orange
			App->render->DrawQuad(colliders[i]->rect, 255, 127, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_POWER_UP: //pink
			App->render->DrawQuad(colliders[i]->rect, 255, 192, 203, alpha);
			break;
		case COLLIDER_COIN: //black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;

		case COLLIDER_HITBOX: //cyan
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 232, alpha);
			break;
		case COLLIDER_TRIGGER: //dark pink
			App->render->DrawQuad(colliders[i]->rect, 255, 105, 180, alpha);
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}
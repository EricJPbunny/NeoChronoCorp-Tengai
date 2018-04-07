#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleBackground.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender() : Module()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);
	currentTime = SDL_GetTicks();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{

	if (currentTime < 3500) {
		speed = 10.25;
	}
	
	else if (currentTime > 3500 && currentTime < 14000) {
		speed = 6.75;
	}

	else if (currentTime > 14000 && currentTime<18000) {
		speed = 13;
	}

	else if (currentTime > 18000 && currentTime<18500) {
		speed -= 0.17;
	}

	else if (currentTime > 18500 && currentTime < 20000) {
		speed = 0;
	}

	else if (currentTime > 20000 && currentTime<38000) {
		speed = 6.75;
	}
	
	else if (App->render->rect.x < -27000 && App->render->rect.x > -30100 ) {
		App->background->posx -= 1.75;
		App->background->posy += 1.20;
		speed = 6.75;
	}
	else if (App->render->rect.x < -30100) {
		speed = 9;
	}

	if(App->render->rect.x < -24820 && App->render->rect.x > -26000) {
		App->background->grassy += 0.5;
	}

	camera.x -= speed;


	/*if(App->input->keyboard[SDL_SCANCODE_UP] == 1)
	camera.y += speed;

	if(App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
	camera.y -= speed;

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1)
	camera.x -= speed;

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1)
	camera.x += speed;*/

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
{
	bool ret = true;
	
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if(SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}


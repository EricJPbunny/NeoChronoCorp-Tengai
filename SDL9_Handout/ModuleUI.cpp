#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_render.h"


ModuleUI::ModuleUI()
{
	

}

ModuleUI::~ModuleUI()
{}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading UI");
	font_score = App->fonts->Load("fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);
	return true;
}

// UnLoad assets
bool ModuleUI::CleanUp()
{
	LOG("Unloading UI");
	
	return true;
}

// Update: draw background
update_status ModuleUI::Update()
{
	App->fonts->BlitText(34, 34, font_score, "risas");
	return UPDATE_CONTINUE;
}
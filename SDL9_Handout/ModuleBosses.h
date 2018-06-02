#ifndef _MODULE_BOSSES_
#define _MODULE_BOSSES_

#define MAX_BOSSES 5
#include "Module.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "SDL\include\SDL_rect.h"

class Boss;

class ModuleBosses : public Module
{
public:
	ModuleBosses();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	~ModuleBosses();

private:
	
	Boss* bosses[MAX_BOSSES];
	SDL_Texture* boss_sprites;
	SDL_Texture* boss_sprites_2;
	

};
#endif
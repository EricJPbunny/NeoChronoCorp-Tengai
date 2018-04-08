#ifndef __MODULELEVEL2_H__
#define __MODULELEVEL2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
struct SDL_Texture;

class ModuleLevel2 : public Module
{
public:
	ModuleLevel2();
	~ModuleLevel2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music* mus = nullptr;
	SDL_Texture* graphics = nullptr;

	SDL_Rect lev2;
	
};

#endif // __MODULESCENEHONDA_H__